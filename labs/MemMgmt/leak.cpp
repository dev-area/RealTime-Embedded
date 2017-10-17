//====================================================================
// File:        leak.cpp
// Description: Test harness for cell allocation leakage detection
//====================================================================

#include <iostream>
#include <stdlib.h>
#include <stack>
#include "cell.hpp"

using namespace std;

int main()
{
    size_t generations, size;
    cout << "Please enter the number of generations: ";
    cin >> generations;
    cout << "Please enter the size of each generation: ";
    cin >> size;

    for (size_t generation = 0; generation < generations; ++generation)
    {
        cout << endl << "[generation " << generation << "]" << endl;
        stack<cell *> cells;

        for (size_t child = 0; child < size; ++child)
        {
            cells.push(new cell);
            cout << cells.top()->contents() << endl;
        }

        while (!cells.empty())
        {
            if (rand() % 7 != 0)
            {
                delete cells.top();
            }

            cells.pop();
        }
    }

    cout << endl;

    // Report your allocation/deallocation statistics for cell here...

    return 0;
}
