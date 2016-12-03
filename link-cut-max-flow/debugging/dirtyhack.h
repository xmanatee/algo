#ifndef _DIRTYHACK_H_
#define _DIRTYHACK_H_

#include <cassert>

const int MAX_MEM = (const int) 5e8;
int mpos = 0;
char mem[MAX_MEM];

inline void *operator new(size_t n ) {
    char *res = mem + mpos;
    mpos += n;
    assert(mpos <= MAX_MEM);
    return (void *)res;
}

inline void operator delete (void *) { }

#endif // _DIRTYHACK_H_