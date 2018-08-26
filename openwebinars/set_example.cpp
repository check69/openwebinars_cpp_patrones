#include "stl_examples.hpp"

#include <iostream>
#include <set>

// Se usa para incluir todos los elementos pertenicientes de std.
// Nos ahorramos tener que escribir std::
// Normalmente es mejor usar std:: pero para pruebas, se permite usarlo.
using namespace std;

void setExample()
{
    /* Deque container */
    set<int> mySet{ 1, 2, 3, 5, 4, 10, 8, 9 };

    //Ranged base loop.
    for (auto& elem : mySet)
    {
        cout << elem << endl;
    }

    getchar();

    for (auto it = mySet.begin(); it != mySet.end(); ++it)
    {
        cout << *it << endl;
    }

    auto it = mySet.find(5);
    cout << *it << endl;

    if (mySet.find(100) == mySet.end())
        cout << "Element not found" << endl;

    if (mySet.empty())
    {
        cout << "Set is empty" << endl;
    }

    getchar();
}