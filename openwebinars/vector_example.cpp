#include "stl_examples.hpp"

#include <iostream>
#include <vector>

using namespace std;

void vectorExample()
{
    vector<int> myVector{ 1, 2, 3, 5, 4, 10, 8, 9 };

    //Ranged base loop.
    for (auto& elem : myVector)
    {
        cout << elem << endl;
    }

    getchar();

    // Ya que están contiguas en memoria se puede hacer esto.
    for (unsigned int i = 0; i < myVector.size(); ++i)
    {
        cout << myVector[i] << endl;
    }

    getchar();

    for (auto it = myVector.begin(); it != myVector.end();)
    {
        cout << *it << endl;
        it = myVector.erase(it);
    }

    if (myVector.empty())
    {
        cout << "Vector is empty" << endl;
    }

    getchar();
}