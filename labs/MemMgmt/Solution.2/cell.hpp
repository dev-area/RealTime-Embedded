
//====================================================================
// File:        cell.hpp
// Description: Definition of cell class
//====================================================================

#ifndef CELL_INCLUDED
#define CELL_INCLUDED

class cell
{
public:

    cell();
    ~cell();

    const char * contents() const;

    void * operator new(size_t);
    void operator delete(void *);

    static size_t allocated();
    static size_t deallocated();

private:

    char * text;

    static size_t newed, deleted;

    cell(const cell &);
    cell & operator=(const cell &);

};

#endif // header already included
