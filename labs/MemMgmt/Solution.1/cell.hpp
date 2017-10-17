
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

private:

    char * text;

    cell(const cell &);
    cell & operator=(const cell &);

};

#endif // header already included
