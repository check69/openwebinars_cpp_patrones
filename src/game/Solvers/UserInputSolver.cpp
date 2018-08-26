#include "UserInputSolver.hpp"

#include <game/Actions/ActionCallable.hpp>
#include <game/Actions/ActionSimpleMoveDiamond.hpp>
#include <game/Actions/ActionSwapMoveDiamond.hpp>
#include <game/Actions/ActionBlink.hpp>

#include <utility>
#include <algorithm>

UserInputSolver::UserInputSolver(Engine& engine,
                                    Map& grid2D,
                                    float& timeDelta,
                                    bool& checkflag) :
    m_engine(engine),
    m_initGraphicMap(),
    m_clicked(false),
    m_unclicked(false),
    m_posSaved(false),
    m_initCellX(0),
    m_initCellY(0),
    m_initPosition(0.f,0.f),
    m_timeDelta(timeDelta),
    m_grid(grid2D),
    m_checkflag(checkflag),
    m_actionBlink(nullptr)
{
}

ActionPtr UserInputSolver::check()
{
    switch(getState())
    {
        case STATE::FIRST_CLICK:
        {
            vec2 pos = getMousePosition();
            int x,y;
            if(checkCollisionWithCell(pos,x,y))
            {
                m_initPosition = pos;
                saveInitPosition(x,y);
                m_unclicked = false;
                m_posSaved = true;
                m_actionBlink.reset(new ActionBlink(m_grid.getCell(y, x),
                                                    m_timeDelta,
                                                    m_initGraphicMap.getBlinkDiamond()));
                m_actionBlink->activate();
                return m_actionBlink;
            }
            else
            {
                m_clicked = false;
                m_actionBlink->finish();
            }
            break;
        }

        case STATE::SECOND_CLICK:
        {
            vec2 pos = getMousePosition();
            int x,y;
            if(checkCollisionWithCell(pos, x, y))
            {
                if(vec2(m_initCellX,m_initCellY) != vec2(x,y))
                {
                    vec2 distance(abs(static_cast<int>(x - m_initCellX)),abs(static_cast<int>(y - m_initCellY)));
                    if(distance.x > 1 || distance.y > 1 || distance == vec2(1,1))
                    {
                        saveInitPosition(x,y);
                        m_unclicked = false;
                        m_actionBlink->finish();
                        m_actionBlink.reset(new ActionBlink(m_grid.getCell(y, x),
                                                            m_timeDelta,
                                                            m_initGraphicMap.getBlinkDiamond()));
                    }
                    else
                    {
                        return moveDiamonds(x, y);
                    }
                }
            }
            else
            {
                m_clicked = false;
                m_actionBlink->finish();
            }
            break;
        }
        case STATE::SWIPING:
        {
            if(m_posSaved)
            {
                vec2 pos = getMousePosition();
                int x,y;
                if(checkCollisionWithCell(pos,x,y))
                {
                    if(vec2(x,y) != vec2(m_initCellX,m_initCellY))
                    {
                        return calcSwip();
                    }
                }
                else
                {
                    return calcSwip();
                }
            }

            break;
        }
        case STATE::UNCLICK:
        {
            if(m_posSaved)
            {
                vec2 pos = getMousePosition();
                int x,y;
                if(checkCollisionWithCell(pos,x,y))
                {
                    if(vec2(m_initCellX,m_initCellY) == vec2(x,y))
                    {
                        m_actionBlink->finish();
                        m_posSaved = false;
                        m_unclicked = false;
                    }
                }
            }

            break;
        }

        default:
            break;
    }

    return nullptr;
}

bool UserInputSolver::checkCollisionWithCell (vec2& position,int& cellCol,int& cellRow)
{
    if(position.x < m_initGraphicMap.GetEndPositionX() &&
        position.x > m_initGraphicMap.GetStartPositionX())
    {
        if(position.y < m_initGraphicMap.GetEndPositionY() &&
            position.y > m_initGraphicMap.GetStartPositionY())
        {
            cellRow = static_cast<int>(trunc((position.x - m_initGraphicMap.GetStartPositionX()) / m_initGraphicMap.GetSizeX()));
            cellCol = static_cast<int>(trunc((position.y - m_initGraphicMap.GetStartPositionY()) / m_initGraphicMap.GetSizeY()));

            return true;
        }
    }

    return false;
}

UserInputSolver::STATE UserInputSolver::getState()
{
    if(m_engine.GetMouseButtonDown())
    {
        if(!m_clicked)
        {
            m_clicked = true;
            if(!m_posSaved)
            {
                return STATE::FIRST_CLICK;
            }
            else
            {
                return STATE::SECOND_CLICK;
            }
        }
        else
        {
            return STATE::SWIPING;
        }
    }
    else
    {
        if(m_clicked)
        {
            m_clicked = false;
            if(!m_unclicked)
            {
                m_unclicked = true;
                return STATE::IDLE;
            }

            return STATE::UNCLICK;
        }
    }

    return STATE::IDLE;
}

ActionPtr UserInputSolver::moveDiamonds(int x, int y)
{
    m_actionBlink->finish();
    m_unclicked = false;
    m_posSaved = false;

    DiamondPtr obj1(m_grid.getCell(m_initCellY,m_initCellX));
    DiamondPtr obj2(m_grid.getCell(y,x));

    ActionBlockingStackPtr stack(new ActionBlockingStack());
    stack->addAction(ActionPtr(new ActionCallable([this](){m_checkflag = false;})));
    ActionPtr simpleMove(new ActionSimpleMoveDiamond(obj1,obj2,m_timeDelta,m_initGraphicMap.getSpeedDiamond()));
    ActionPtr actions{};
    if(!fastCheck(obj1,obj2,m_initCellY,m_initCellX,y,x))
    {
        stack->addAction(ActionPtr(new ActionSwapMoveDiamond(obj1,obj2,m_timeDelta,m_initGraphicMap.getSpeedDiamond())));
    }
    else
    {
        m_grid.setElement(y,x,obj1);
        m_grid.setElement(m_initCellY,m_initCellX,obj2);
        stack->addAction(simpleMove);
    }
    stack->addAction(ActionPtr(new ActionCallable([this](){m_checkflag = true;})));

    return stack;
}

void UserInputSolver::saveInitPosition (int x,int y)
{
    m_initCellX = x;
    m_initCellY = y;
}

vec2 UserInputSolver::getMousePosition ()
{
    return vec2(m_engine.GetMouseX(),m_engine.GetMouseY());
}
    
ActionPtr UserInputSolver::calcSwip ()
{
    DIRECTION dir = calcDirection();
    int x = m_initCellX;
    int y = m_initCellY;

    switch(dir)
    {
    case DIRECTION::UP:
    {
        if(m_initCellX > 0)
        {
            x = m_initCellX - 1;
        }
        break;
    }
    case DIRECTION::DOWN:
    {
        if(m_initCellX < m_initGraphicMap.GetHeight() - 1)
        {
            x = m_initCellX + 1;
        }
        break;
    }
    case DIRECTION::LEFT:
    {
        if(m_initCellY > 0)
        {
            y = m_initCellY - 1;
        }
        break;
    }
    case DIRECTION::RIGHT:
    {
        if(m_initCellY < m_initGraphicMap.GetWidth() - 1)
        {
            y = m_initCellY + 1;
        }
        break;
    }
    }

    if(vec2(x,y) != vec2(m_initCellX,m_initCellY))
    {
        m_unclicked = false;
        m_posSaved = false;

        return moveDiamonds(x, y);
    }

    return nullptr;
}

UserInputSolver::DIRECTION UserInputSolver::calcDirection ()
{
    vec2 mousePosition = getMousePosition();
    vec2 uX(1.f,0.f);
    vec2 uY(0.f,1.f);
    vec2 dir(mousePosition.x - m_initPosition.x,
                mousePosition.y - m_initPosition.y);
    float xRes = uX.x*dir.x;
    float yRes = uY.y*dir.y;

    if(abs(xRes) > abs(yRes))
    {
        if(xRes > 0)
        {
            return DIRECTION::RIGHT;
        }

        return DIRECTION::LEFT;
    }

    if(yRes > 0)
    {
        return DIRECTION::DOWN;
    }

    return DIRECTION::UP;
}

bool UserInputSolver::fastCheckRow (unsigned int texture, unsigned int column, const unsigned int row)
{
    int moveColumn = column;
    unsigned int equals = 1;

    while(++moveColumn < static_cast<int>(m_initGraphicMap.GetWidth()) && m_grid.getCell(moveColumn, row)->getTexture() == texture)
    {
        ++equals;
    }

    moveColumn = column;
    while(--moveColumn >= 0 && m_grid.getCell(moveColumn,row)->getTexture() == texture)
    {
        ++equals;
    }

    return (equals >= m_initGraphicMap.getMinMatch());
}

bool UserInputSolver::fastCheckColumn (unsigned int texture, const unsigned int column, unsigned int row)
{
    int moveRow = row;
    unsigned int equals = 1;

    while(++moveRow < static_cast<int>(m_initGraphicMap.GetHeight()) && m_grid.getCell(column, moveRow)->getTexture() == texture)
    {
        ++equals;
    }

    moveRow = row;
    while(--moveRow >= 0 && m_grid.getCell(column, moveRow)->getTexture() == texture)
    {
        ++equals;
    }

    return (equals >= m_initGraphicMap.getMinMatch());
}

bool UserInputSolver::fastCheck (DiamondPtr obj1, DiamondPtr obj2, 
                                    unsigned int column1, unsigned int row1, 
                                    unsigned int column2, unsigned int row2)
{
    std::swap(obj1->getTexture(), obj2->getTexture());
        
    bool ret = (fastCheckColumn(obj1->getTexture(), column1, row1)  ||
                fastCheckColumn(obj2->getTexture(), column2, row2)  ||
                fastCheckRow(obj1->getTexture(), column1, row1)     ||
                fastCheckRow(obj2->getTexture(), column2, row2));

    std::swap(obj1->getTexture(), obj2->getTexture());

    return ret;
}