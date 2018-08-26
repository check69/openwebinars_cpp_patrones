#include "stl_examples.hpp"

#include <iostream>

// Se usa para incluir todos los elementos pertenicientes de std.
// Nos ahorramos tener que escribir std::
// Normalmente es mejor usar std:: pero para pruebas, se permite usarlo.
using namespace std;

int main()
{
    basicArrayExample();
    vectorExample();
    dequeExample();
    listExample();
    setExample();
    mapExample();

    return 0;
}