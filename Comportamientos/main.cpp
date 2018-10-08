#include "observer.hpp"

#include <iostream>

int main()
{
    Subject s;

    s.addObserver(std::shared_ptr<Observer>(new SubjectObserver));
    s.addObserver(std::shared_ptr<Observer>(new SubjectObserver));

    s.do_something();

    getchar();
    return 0;
}