#ifndef __SOLVER_EXAMPLE_HPP__
#define __SOLVER_EXAMPLE_HPP__

#include "Solver.hpp"
#include "ActionCallable.hpp"

#include <iostream>
#include <functional>
#include <vector>

void g()
{
    std::cout << "Eureka, it works" << std::endl;
}

class SolverExample : public Solver
{
    public:
                            SolverExample   () {}
                           ~SolverExample   () {}

                void        addMethod       (std::function<bool()> method)
                {
                    m_vFunctions.push_back(method);
                }
        virtual ActionPtr check () override
           {
                for (auto& elem : m_vFunctions)
                {
                    if (elem())
                    {
                        auto ptr = std::make_shared<ActionCallable>(&g);
                        ptr->activate();
                        return ptr;
                    }
                }

                return nullptr;
           }

    private:
        std::vector<std::function<bool()>> m_vFunctions{};
        

};

#endif
