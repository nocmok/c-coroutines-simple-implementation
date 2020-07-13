#include <coro.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

coro_t coro0, coro1;

void f0(coro_t *coro){
    assert(coro->state == RUNNING);
    
    puts("f0");
    coro_yield(&coro1);
    puts("f0");
    coro_yield(&coro1);
    puts("last f0");
}

void f1(coro_t *coro){
    assert(coro->state == RUNNING);

    puts("f1");
    coro_yield(&coro0);
    puts("f1");
}

int main(){
    coro_init(&coro0, (coro_fn)f0, NULL);
    coro_init(&coro1, (coro_fn)f1, NULL);

    coro_start(&coro0);

    assert(coro0.state == FINISHED);
    assert(coro1.state == FINISHED);

    puts("coroutines done their work");

    coro_free(&coro0);
    coro_free(&coro1);

    exit(0);
}