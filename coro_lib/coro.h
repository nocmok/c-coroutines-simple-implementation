#ifndef CORO_H
#define CORO_H

#include <ucontext.h>

#define CORO_DEFAULT_STACK_SIZE 4096

typedef struct coro_t coro_t;
typedef enum coro_state coro_state;

typedef void (*coro_fn)(coro_t *coro);

enum coro_state {
    NEW,
    RUNNING,
    FINISHED,
    FREE
};

struct coro_t {
    coro_state state;

    size_t stack_size;
    void *stack;

    coro_fn func;

    ucontext_t this_context;
    /* helps to transfer control to execution context of caller, if coroutine done all it's work.
    * Since other coroutine may appear as the caller, so the context may changes dynamically, 
    * this field holds pointer to context, not context itself.
     */
    ucontext_t *caller_context;
};

void coro_init(coro_t *coro, coro_fn func);
void coro_yield(coro_t *next);
void coro_start(coro_t *coro);
void coro_free(coro_t *coro); 

#endif