#ifndef __INIT_GAME_HPP__
#define __INIT_GAME_HPP__

#include <game/Actions/ActionBlockingStack.hpp>
#include <game/Solvers/Solver.hpp>
#include <game/Solvers/SolverStack.hpp>
#include <game/InitGraphicMap.hpp>
#include <game/Map.hpp>

#include <graphic/Engine.h>
#include <graphic/Updater.h>

#include <map>
#include <memory>

class InitGame : public Updater
{
    public:
                InitGame       ();
            ~InitGame       ();

        void start          ();
        void Update         ();
        void showTime       ();
        void showScore      ();
        void showFinalScore ();
        void BuildMap       ();

    private:
        Engine                                          m_engine;
        float                                           m_fTimeDelta;
        float                                           m_fTargetTime;
        ActionStack                                     m_actions;
        SolverStack                                     m_solvers;
        SolverPtr                                       m_inputSolver;
        std::map<std::string, std::shared_ptr<Action>>  m_rememberActions{};
        Map                                             m_map;
        InitGraphicMap                                  m_graphicMap;
        bool                                            m_checkflag;
        unsigned int                                    m_score;
};

#endif //__DIAMOND_HPP__