#ifndef __USERINPUTSOLVER_HPP__
#define __USERINPUTSOLVER_HPP__

#include <game/Map.hpp>
#include <game/InitGraphicMap.hpp>
#include <game/Actions/Action.hpp>
#include <game/Diamond.hpp>
#include <game/Solvers/Solver.hpp>
#include <utils/math.hpp>

#include <graphic/Engine.h>

#include <math.h>
#include <iostream>
#include <memory>

/*
The user input solver handle user input, mainly 2 gestures:
Touch-Touch for swapping
Swiping for swapping
It generates either a simple diamond move or a double swap move Action
*/

class UserInputSolver : public Solver
{
    public:
        enum class STATE
        {
            IDLE,
            FIRST_CLICK,
            SECOND_CLICK,
            SWIPING,
            UNCLICK,
        };

                            UserInputSolver (Engine& engine,
                                                Map& grid2D,
                                                float& timeDelta,
                                                bool& checkflag);

        virtual ActionPtr   check           () override;

    private:
        enum class DIRECTION
        {
            UP = 0,
            RIGHT,
            DOWN,
            LEFT,
        };

        bool        checkCollisionWithCell  (vec2& position, int& cellRow, int& cellCol);
        STATE       getState                ();
        void        saveInitPosition        (int x, int y);
        vec2        getMousePosition        ();
        ActionPtr   moveDiamonds            (int x, int y);
        ActionPtr   calcSwip                ();
        DIRECTION   calcDirection           ();
        bool        fastCheckRow            (unsigned int texture,
                                                unsigned int column,
                                                const unsigned int row);
        bool        fastCheckColumn         (unsigned int texture,
                                                const unsigned int column,
                                                unsigned int row);
        bool        fastCheck               (DiamondPtr obj1, DiamondPtr obj2,
                                                unsigned int column1, unsigned int row1,
                                                unsigned int column2, unsigned int row2);

        Engine&   m_engine;
        InitGraphicMap  m_initGraphicMap;
        bool            m_clicked;
        bool            m_unclicked;
        bool            m_posSaved;
        unsigned int    m_initCellX;
        unsigned int    m_initCellY;
        vec2            m_initPosition;
        float&          m_timeDelta;
        Map&            m_grid;
        bool&           m_checkflag;
        ActionPtr       m_actionBlink;
};

#endif // !__USERINPUTSOLVER_HPP__