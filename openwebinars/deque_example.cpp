#include "stl_examples.hpp"

#include <iostream>
#include <deque>

// Se usa para incluir todos los elementos pertenicientes de std.
// Nos ahorramos tener que escribir std::
// Normalmente es mejor usar std:: pero para pruebas, se permite usarlo.
using namespace std;

void dequeExample()
{
    /* Deque container */
    deque<int> myDeque{ 1, 2, 3, 5, 4, 10, 8, 9 };

    //Ranged base loop.
    for (auto& elem : myDeque)
    {
        cout << elem << endl;
    }

    getchar();

    // Ya que están contiguas en memoria se puede hacer esto.
    for (unsigned int i = 0; i < myDeque.size(); ++i)
    {
        cout << myDeque[i] << endl;
    }

    getchar();

    for (auto it = myDeque.begin(); it != myDeque.end();)
    {
        cout << *it << endl;
        it = myDeque.erase(it);
    }

    if (myDeque.empty())
    {
        cout << "Deque is empty" << endl;
    }

    getchar();
}