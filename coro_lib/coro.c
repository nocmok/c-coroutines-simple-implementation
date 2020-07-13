#include <stdlib.h>
#include "coro.h"

static coro_t *coro_curr = NULL;

void coro_wrapper(coro_t *coro){
    coro->state = RUNNING;
    coro_curr = coro;
    (*coro->func)(coro, coro->args);
    coro->state = FINISHED;
    swapcontext(&coro->this_context, coro->caller_context);
}

void coro_init(coro_t *coro, coro_fn func, void *args){
    coro->state = NEW;
    coro->stack_size = CORO_DEFAULT_STACK_SIZE;
    coro->stack = malloc(coro->stack_size);
    coro->args = args;
    coro->func = func;
    
    getcontext(&coro->this_context);
    coro->this_context.uc_stack.ss_size = coro->stack_size;
    coro->this_context.uc_stack.ss_sp = coro->stack;
    makecontext(&coro->this_context, (void(*)())coro_wrapper, 1, coro);

    coro->caller_context = NULL;
}

void coro_yield(coro_t *next){
    if(next->state != NEW && next->state != RUNNING){
        return;
    }
    coro_t *cc = coro_curr;
    coro_curr = next;
    if(next->state == NEW){
        next->caller_context = &cc->this_context;
    }
    swapcontext(&cc->this_context, &next->this_context);
}

void coro_start(coro_t *coro){
    if(coro->state != NEW){
        return;
    }
    ucontext_t caller_context;
    coro->caller_context = &caller_context;
    swapcontext(coro->caller_context, &coro->this_context);
}

void coro_free(coro_t *coro){
    if(coro->state == RUNNING){
        return;
    }
    free(coro->stack);
    coro->state = FREED;
}