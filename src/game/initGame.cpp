#include "initGame.hpp"

#include <game/Actions/TimeDecreaseAction.hpp>
#include <game/Actions/ActionGenerateDiamond.hpp>
#include <game/Actions/ActionCallable.hpp>
#include <game/Solvers/UserInputSolver.hpp>
#include <game/Solvers/SolverGrid2D.hpp>
#include <game/Solvers/SolverRefill.hpp>
#include <utils/math.hpp>

#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>

namespace testGame
{
    const std::string pathAssets = "./assets";
    const float targetTime = 60.f;
    
    InitGame::InitGame() :
        m_engine(pathAssets.c_str()),
        m_fTimeDelta(0.f),
        m_fTargetTime(targetTime),
        m_actions(),
        m_map(),
        m_graphicMap(),
        m_checkflag(true),
        m_inputSolver(nullptr),
        m_score(0)
    {
    }

    InitGame::~InitGame ()
    {
    }

    void InitGame::start ()
    {
        BuildMap();
        m_inputSolver.reset(new UserInputSolver(m_engine,
                                                m_map,
                                                m_fTimeDelta,
                                                m_checkflag));
        m_solvers.addSolver(SolverPtr(new SolverGrid2D(m_map,
                                                       m_checkflag,
                                                       m_fTimeDelta,
                                                       m_score)));
        m_rememberActions["TimeDecrease"] = std::shared_ptr<Action>(new TimeDecrease(m_fTimeDelta,
                                                                                     m_fTargetTime));
        m_actions.addAction(m_rememberActions["TimeDecrease"]);
        m_actions.activateAll();
        m_engine.Start(*this);
    }

    void InitGame::BuildMap()
    {
        for(unsigned short column = 0; column < m_graphicMap.GetWidth(); ++column)
        {
            for(unsigned short row = 0; row < m_graphicMap.GetHeight(); ++row)
            {
                DiamondPtr d(new Diamond());
                d->setPosition(m_map.getCellPos(column, row));
                m_map.setElement(column, row, d);
                ActionPtr action(new ActionGenerateDiamond(d));
                m_actions.addAction(action);
            }
        }
    }

    void InitGame::Update ()
    {
        m_fTimeDelta = m_engine.GetLastFrameSeconds();
        m_engine.Render(Engine::TEXTURE_BACKGROUND, 0, 0);

        if (m_actions.getState() == Action::STATE::RUNNING)
        {
            if (m_checkflag)
            {
                ActionPtr inputAction(m_inputSolver->check());
                if(inputAction)
                {
                    m_actions.addAction(inputAction);
                    inputAction->activateAll();
                }
            }

            m_actions.execute();
        }

        if(m_checkflag)
        {
            ActionPtr action = m_solvers.check();
            if (action)
            {
                m_actions.addAction(action);
                action->activateAll();
            }
        }

        for(unsigned short column = 0; column < m_graphicMap.GetWidth(); ++column)
        {
            for(unsigned short row = 0; row < m_graphicMap.GetHeight(); ++row)
            {
                std::shared_ptr<Diamond> d(m_map.getCell(column, row));

                if (d && d->getRendeable())
                {
                    auto pos = d->getPosition();
                    Engine::Texture t = static_cast<Engine::Texture>(d->getTexture());
                    if (t >= 0)
                    {
                        m_engine.Render(t, pos.x, pos.y);
                    }
                }
            }
        }

        m_engine.Render(Engine::TEXTURE_BACKGROUND_ALPHA,0,0);

        showTime();

        if (m_fTargetTime <= 0.f)
        {
            showFinalScore();
            m_checkflag = false;
        }
        else
        {
            showScore();
        }
    }

    void InitGame::showTime ()
    {
        std::stringstream timeToString;
        timeToString << std::fixed << std::setprecision(0) << ceil(m_fTargetTime);
        m_engine.Write(timeToString.str().c_str(),
                       transform(translate(85.f,420.f),
                       scale(2.f,2.f)));
    }

    void InitGame::showScore ()
    {
        std::stringstream timeToString;
        timeToString << "Score: " << std::fixed << std::setprecision(0) << m_score;
        m_engine.Write(timeToString.str().c_str(),
                       transform(translate(30.f,100.f),
                       scale(1.5f,1.5f)));
    }
    
    void InitGame::showFinalScore ()
    {
        std::stringstream timeToString;
        timeToString << "Your final score is " << std::fixed << std::setprecision(0) << m_score;
        m_engine.Write(timeToString.str().c_str(),
                       transform(translate(90.f,250.f),
                       scale(2.f,2.f)));
    }
}