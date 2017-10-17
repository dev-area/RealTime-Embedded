
//====================================================================
// File:        cell.cpp
// Description: Definition of cell class member functions
//====================================================================

#include <stdlib.h>
#include "cell.hpp"

cell::cell()
  : text(0)
{
    size_t length = rand() % 80;
    text = (char *) ::operator new(length + 1);

    static const char chars[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789!\"$%^&*()-+=_/\\.,?;:'@#~[]{}|";

    for (size_t current = 0; current < length; ++current)
    {
        text[current] = chars[rand() % (sizeof chars - 1)];
    }

    text[length] = '\0';
}

cell::~cell()
{
    ::operator delete(text);
}

const char * cell::contents() const
{
    return text;
}

cache cell::spare;

void * cell::operator new(size_t size)
{
    void * result = spare.get();

    if (!result)
    {
        result = ::operator new(size);
    }

    return result;
}

void cell::operator delete(void * ptr)
{
    if (ptr)
    {
        spare.put(ptr);
    }
}
