#ifndef __SOLVER_HPP__
#define __SOLVER_HPP__

#include "Action.hpp"

#include <memory>

class Solver
{
public:
    virtual ActionPtr   check   () = 0;
};

using SolverPtr = std::shared_ptr<Solver>;

#endif // !__SOLVER_H_