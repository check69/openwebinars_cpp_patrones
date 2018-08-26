#ifndef __SOLVERSTACK_HPP__
#define __SOLVERSTACK_HPP__

#include "Solver.hpp"
#include <game/Actions/ActionBlockingStack.hpp>

#include <list>
#include <memory>

class SolverStack : public Solver
{
    public:
                    SolverStack()                               {}
                    SolverStack(std::list<SolverPtr> solvers) :
                        m_solvers(solvers)                      {}
                    virtual ~SolverStack()                       {}

        ActionPtr   check() override
        {
            bool isReturnActions = false;
            ActionBlockingStackPtr actions(new ActionBlockingStack());
            for (auto solver : m_solvers)
            {
                ActionPtr action(solver->check());
                if (action)
                {
                    isReturnActions = true;
                    actions->addAction(action);
                }
            }

            if (isReturnActions)
            {
                return actions;
            }
            else
            {
                return nullptr;
            }
        }

        void addSolver(SolverPtr solver)
        {
            m_solvers.push_back(solver);
        }

    private:
        std::list<SolverPtr> m_solvers{};
};

#endif //!__SOLVERSTACK_HPP__