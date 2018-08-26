#ifndef __SOLVER_HPP__
#define __SOLVER_HPP__

#include <game/Actions/Action.hpp>

#include <memory>
/*
Solver is the base abstract class for all the checking within the game
A solver must implement the check method which should return the actions
to reply to the checking
*/
class Solver
{
    public:
        virtual ActionPtr   check   ()  = 0;
};

using SolverPtr = std::shared_ptr<Solver>;

#endif // !__SOLVER_H_