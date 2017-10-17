
//====================================================================
// File:        cache.hpp
// Description: Definition of cache class
//====================================================================

#ifndef CACHE_INCLUDED
#define CACHE_INCLUDED

#include <qa/stack.hpp>
#include <qa/list.hpp>

using namespace qa;

class cache
{
public:

    cache();
    ~cache();

    void * get();
    void put(void *);

private:

    stack<void *> blocks;

    cache(const cache &);
    cache & operator=(const cache &);

};

#endif // header already included
