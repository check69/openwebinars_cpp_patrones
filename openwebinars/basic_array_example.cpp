#include "stl_examples.hpp"

#include <iostream>
#include <deque>

// Se usa para incluir todos los elementos pertenicientes de std.
// Nos ahorramos tener que escribir std::
// Normalmente es mejor usar std:: pero para pruebas, se permite usarlo.
using namespace std;

void basicArrayExample()
{
    int myArray[8]{ 1, 2, 3, 5, 4, 10, 8, 9 };

    for (unsigned i = 0; i < 8; ++i)
    {
        cout << myArray[i] << endl;
    }

    getchar();
}