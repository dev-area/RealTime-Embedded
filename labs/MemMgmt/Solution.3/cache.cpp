
//====================================================================
// File:        cache.cpp
// Description: Definition of cache class member functions
//====================================================================

#include "cache.hpp"

cache::cache()
{
}

cache::~cache()
{
    while (!blocks.empty())
    {
        operator delete(blocks.top());
        blocks.pop();
    }
}

void * cache::get()
{
    void * result = 0;

    if (!blocks.empty())
    {
        result = blocks.top();
        blocks.pop();
    }

    return result;
}

void cache::put(void * ptr)
{
    blocks.push(ptr);
}
