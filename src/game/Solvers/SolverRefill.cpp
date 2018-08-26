#include "SolverRefill.hpp"

namespace testGame
{
    SolverRefill::SolverRefill(Map& map,
                               const float&    timedelta) :
        m_map    (map),
        m_graphicMap(),
        m_timedelta   (timedelta)
    {
    }

    SolverRefill::~SolverRefill() {}

    ActionPtr SolverRefill::check ()
    {
        bool refill = false;
        ActionStackPtr stack(new ActionStack());
        for (unsigned int column = 0; column < m_graphicMap.GetWidth(); ++column)
        {
            unsigned int numberGap = 0;
            std::list<DiamondPtr> listDiamond{};
            for (int row = m_graphicMap.GetHeight() - 1; row >= 0; --row)
            {
                DiamondPtr d(m_map.getCell(column, row));

                if (!d || !d->isActive())
                {
                    if (!d)
                    {
                        d.reset(new Diamond());
                        m_map.setElement(column, row, d);
                    }

                    ++numberGap;
                    d->setPosition(m_map.getCellSpawnPos(column, m_graphicMap.GetHeight() - numberGap));
                    listDiamond.push_back(d);
                }
                else
                {
                    if (listDiamond.size())
                    {
                        refill = true;
                        d = m_map.getCell(column, row);
                        m_map.setElement(column, row + numberGap, d);
                        stack->addAction(ActionPtr(new ActionMove(d->getPosition(),
                                                                  m_map.getCellPos(column, row + numberGap),
                                                                  m_timedelta,
                                                                  m_graphicMap.getSpeedDiamond())));
                    }
                }
            }

            for (int i = --numberGap; i >= 0; --i)
            {
                refill = true;
                DiamondPtr d(listDiamond.front());
                listDiamond.pop_front();
                m_map.setElement(column, i, d);
                ActionBlockingStackPtr blockingStack(new ActionBlockingStack
                (
                    {
                        ActionPtr(new ActionGenerateDiamond(d)),
                        ActionPtr(new ActionCallable
                        (
                            [d]() { d->setRendeable(true); d->setActive(true); d->dontAllowInteractive(); }
                        )),
                        ActionPtr(new ActionMove(d->getPosition(),
                                                    m_map.getCellPos(column, i),
                                                    m_timedelta,
                                                    m_graphicMap.getSpeedDiamond())),
                        ActionPtr(new ActionCallable
                        (
                            [d]() { d->allowInteractive(); d->setActive(true); }
                        )),
                    }
                ));
                stack->addAction(blockingStack);
            }
        }

        if (refill)
        {
            return stack;
        }

        return nullptr;
    }
}