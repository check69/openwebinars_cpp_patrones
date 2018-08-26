#include "SolverGrid2D.hpp"
#include <game/Solvers/SolverRefill.hpp>

#include <vector>

namespace testGame
{
    SolverGrid2D::SolverGrid2D(Map& grid,
                               bool&        checkflag,
                               const float& timedelta,
                               unsigned int&  score) :
        SolverStack({SolverPtr(new SolverRefill(grid, timedelta))}),
        m_grid(grid),
        m_graphicMap(),
        m_checkFlag(checkflag),
        m_timedelta(timedelta),
        m_score(score)
    { }

    ActionPtr SolverGrid2D::check ()
    {
        bool isReturnedAction = false;
        ActionStackPtr stack(new ActionStack());
        std::vector<std::vector<std::vector<DiamondPtr>>> toExplodeRow;
        std::vector<std::vector<std::vector<DiamondPtr>>> toExplodeColumn;

        for(unsigned int column = 0; column < m_graphicMap.GetWidth(); ++column)
        {
            std::vector<DiamondPtr> gridColumn(m_grid.getColumn(column));
            if (gridColumn.size())
            {
                auto ret = checkLine(gridColumn);
                if (ret.size())
                {
                    toExplodeColumn.push_back(ret);
                }
            }
        }

        for(unsigned int row = 0; row < m_graphicMap.GetHeight(); ++row)
        {
            std::vector<DiamondPtr> gridRow(m_grid.getRow(row));
            if(gridRow.size())
            {
                auto ret = checkLine(gridRow);
                if(ret.size())
                {
                    toExplodeColumn.push_back(ret);
                }
            }
        }

        if (toExplodeRow.size())
        {
            isReturnedAction = true;
            stack->addAction(explode(toExplodeRow));
        }

        if(toExplodeColumn.size())
        {
            isReturnedAction = true;
            stack->addAction(explode(toExplodeColumn));
        }

            if (isReturnedAction)
            {
                ActionBlockingStackPtr blockStack(new ActionBlockingStack());
                blockStack->addAction(ActionPtr(new ActionCallable([this](){m_checkFlag = false;})));
                blockStack->addAction(stack);
                ActionPtr refillActions(SolverStack::check());
                if (refillActions)
                {
                    blockStack->addAction(refillActions);
                }

                blockStack->addAction(ActionPtr(new ActionCallable([this](){m_checkFlag = true;})));
                return blockStack;
            }

        return nullptr;
    }

    SolverGrid2D::~SolverGrid2D() {}

    ActionPtr SolverGrid2D::explode (std::vector<std::vector<std::vector<DiamondPtr>>>& toExplode)
    {
        ActionStackPtr stack(new ActionStack());
        for (auto& v1: toExplode)
        {
            for(auto& v: v1)
            {
                for(DiamondPtr& d: v)
                {
                    if(d->isActive())
                    {
                        d->setActive(false);
                        stack->addAction(ActionPtr(new ActionCallable
                        (
                            [d]()
                            {
                                d->setRendeable(false);
                                d->dontAllowInteractive();
                            }
                        )));
                        stack->addAction(ActionPtr(new ActionUpgradeScore(m_graphicMap.getScoreDiamond(), m_score)));
                    }
                }
            }
        }

        return stack;
    }

    std::vector<std::vector<DiamondPtr>> SolverGrid2D::checkLine(std::vector<DiamondPtr> grid)
    {
        std::vector<DiamondPtr> match;
        std::vector<std::vector<DiamondPtr>> toExplode{};
        DiamondPtr itActual(grid[0]);
        match.push_back(itActual);

        unsigned short inARow = 1;

        for(unsigned int i = 1; i < grid.size(); ++i)
        {
            DiamondPtr itNext(grid[i]);
            bool newElement = true;

            if(itActual->isActive() &&
                itActual->getTexture() == itNext->getTexture())
            {
                newElement = false;
                ++inARow;
                match.push_back(itNext);
            }

            if(newElement || i == grid.size() - 1)
            {
                if(inARow >= m_graphicMap.getMinMatch())
                {
                    toExplode.push_back(match);
                }
                inARow = 1;
                match.clear();
                match.push_back(itNext);
            }
            itActual = itNext;
        }

        return toExplode;
    }
}