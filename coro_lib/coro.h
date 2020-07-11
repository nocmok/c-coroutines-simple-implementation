#ifndef CORO_H
#define CORO_H

#include <ucontext.h>

#define CORO_DEFAULT_STACK_SIZE 4096

typedef struct coro_t coro_t;

typedef void (*coro_fn)();

struct coro_t {
    
    size_t stack_size;
    void *stack;

    coro_fn func;

    ucontext_t this_context;
    ucontext_t caller_context;
};

coro_t *coro_curr();
void coro_init(coro_t *coro, coro_fn func);

/* transfers control to execution context of specified coroutine, or to caller execution context if next == NULL */
void coro_yield(coro_t *next);
void coro_start(coro_t *coro);
void coro_free(coro_t *coro); 

#endif