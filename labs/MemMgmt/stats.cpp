
//====================================================================
// File:        stats.cpp
// Description: Test harness for collecting allocation stats
//====================================================================

#include <iostream>
#include <stdlib.h>
#include <stack>
#include "cell.hpp"

using namespace std;

// Provide operators new and delete, and counter variables in this
// source file.

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

    // You will need to report the collected statistics here...

    return 0;
}
