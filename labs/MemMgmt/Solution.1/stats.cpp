
//====================================================================
// File:        stats.cpp
// Description: Test harness for collecting allocation stats
//====================================================================

#include <iostream.h>
#include <stdlib.h>
#include <qa/stack.hpp>
#include "cell.hpp"

using namespace qa;

static size_t allocated, deallocated;
static double total_size;

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

    cout << "[allocation stats]" << endl
         << "allocated:    " << allocated << endl
         << "deallocated:  " << deallocated << endl
         << "total bytes:  " << total_size << endl
         << "average size: " << total_size / allocated << endl
         << endl;

    return 0;
}

void * operator new(size_t size)
{
    ++allocated;
    total_size += size;

    return malloc(size); // note that not handling failure case
}

void operator delete(void * ptr)
{
    if (ptr)
    {
        ++deallocated;
        free(ptr);
    }
}
