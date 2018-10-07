#include "observer.hpp"
#include "memento.hpp"

int main ()
{
    Subject s;
    s.addObserver(std::make_shared<SubjectObserver>());
    s.addObserver(std::make_shared<classObserver>());
    s.do_something();
    getchar();

    //Initialize the object, state“Old”
    Originator *o = new Originator("Old");
    o->showState();
    
    //Establish and maintain Memento
    Caretaker* pTaker = new Caretaker();
    pTaker->SetMemento(o->CreateMemento());
    
    //Change state
    o->SetState("New");
    o->showState();
    
    //Restoration of state
    o->RestoreToMemento(pTaker->GetMemento());
    o->showState();
    
    getchar();
    return 0;
}
