#ifndef __SOLVERGRID2D_HPP__
#define __SOLVERGRID2D_HPP__

#include <game/Solvers/SolverStack.hpp>
#include <game/Map.hpp>
#include <game/InitGraphicMap.hpp>
#include <game/Actions/ActionBlockingStack.hpp>
#include <game/Actions/ActionUpgradeScore.hpp>
#include <game/Diamond.hpp>

#include <vector>

namespace testGame
{
    class SolverGrid2D : public SolverStack
    {
        public:
                                SolverGrid2D    (Map& grid,
                                                 bool&        checkflag,
                                                 const float& timedelta,
                                                 unsigned int&  score);

            virtual ActionPtr   check           () override;
            virtual            ~SolverGrid2D    () override;

        private:
            ActionPtr                               explode (std::vector<std::vector<std::vector<DiamondPtr>>>& toExplode);
            std::vector<std::vector<DiamondPtr>>    checkLine(std::vector<DiamondPtr> grid);
             SolverGrid2D   ()          = delete;

            Map&                    m_grid;
            InitGraphicMap          m_graphicMap;
            const float&            m_timedelta;
            bool&                   m_checkFlag;
            unsigned int&           m_score;
    };
}

#endif