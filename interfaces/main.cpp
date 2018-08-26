#include "ActionCallable.hpp"
#include "Action.hpp"
#include "SolverExample.h"

#include <memory>
#include <iostream>


void f()
{
    std::cout << "hola que pasa " << std::endl;
}

bool isTrue()
{
    return true;
}

bool isFalse()
{
    return false;
}

int main()
{
    //ActionPtr action(std::make_shared<Action>(Action()));
    ActionPtr actionCallable(std::make_shared<ActionCallable>(&f));

    actionCallable->execute();
    actionCallable->activate();
    actionCallable->execute();

    getchar();

    SolverExample solver;
    solver.addMethod(&isFalse);

    ActionPtr a(solver.check());

    if (a)
    {
        a->execute();
        getchar();
    }

    solver.addMethod(&isTrue);

    a = solver.check();

    if (a)
    {
        a->execute();
    }

    getchar();
    return 0;
}