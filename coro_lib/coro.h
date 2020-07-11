#ifndef CORO_H
#define CORO_H

#include <ucontext.h>

typedef struct coro_t coro_t;
typedef struct yield_buf yield_buf;

typedef void (*coro_fn)(yield_buf*);

struct yield_buf{
    ucontext_t *caller_context;
    void *data;
};

struct coro_t {
    
    size_t stack_size;
    void *stack;

    coro_fn func;

    ucontext_t this_context;
};

coro_t* coro_curr();
void coro_init(coro_t *coro, coro_fn func);
void coro_yield(coro_t *next, void *data);
void coro_start(coro_t *coro);

#endif