
//====================================================================
// File:        usecell.cpp
// Description: Test harness for opimised cell allocation
//====================================================================

#include <iostream.h>
#include <stdlib.h>
#include <qa/stack.hpp>
#include "cell.hpp"

using namespace qa;

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
            delete cells.top();
            cells.pop();
        }
    }

    cout << endl;

    return 0;
}
