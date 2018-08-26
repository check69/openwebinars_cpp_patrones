#include "stl_examples.hpp"

#include <iostream>
#include <list>

// Se usa para incluir todos los elementos pertenicientes de std.
// Nos ahorramos tener que escribir std::
// Normalmente es mejor usar std:: pero para pruebas, se permite usarlo.
using namespace std;

void listExample()
{
    list<int> myList{ 1, 2, 3, 5, 4, 10, 8, 9 };

    //Ranged base loop.
    for (auto& elem : myList)
    {
        cout << elem << endl;
    }

    getchar();

    for (auto it = myList.begin(); it != myList.end();)
    {
        cout << *it << endl;
        it = myList.erase(it);
    }

    if (myList.empty())
    {
        cout << "List is empty" << endl;
    }

    getchar();
}