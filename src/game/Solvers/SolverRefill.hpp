#ifndef __SOLVERREFILL_HPP__
#define __SOLVERREFILL_HPP__

#include <game/Solvers/Solver.hpp>
#include <game/Map.hpp>
#include <game/InitGraphicMap.hpp>
#include <game/Actions/ActionStack.hpp>
#include <game/Actions/ActionMove.hpp>
#include <game/Actions/ActionBlockingStack.hpp>
#include <game/Actions/ActionGenerateDiamond.hpp>
#include <game/Actions/ActionCallable.hpp>

class SolverRefill : public Solver
{
    public:
                            SolverRefill(Map& map,
                                            const float& timedelta);
        virtual            ~SolverRefill();
        virtual ActionPtr   check () override;

    private:
        Map&            m_map;
        InitGraphicMap  m_graphicMap;
        const float&    m_timedelta;
        SolverRefill() = delete;
};

using SolverRefillPtr = std::shared_ptr<SolverRefill>;

#endif