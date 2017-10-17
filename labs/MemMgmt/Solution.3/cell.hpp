
//====================================================================
// File:        cell.hpp
// Description: Definition of cell class
//====================================================================

#ifndef CELL_INCLUDED
#define CELL_INCLUDED

#include "cache.hpp"

class cell
{
public:

    cell();
    ~cell();

    const char * contents() const;

    void * operator new(size_t);
    void operator delete(void *);

private:

    char * text;

    static cache spare;

    cell(const cell &);
    cell & operator=(const cell &);

};

#endif // header already included
