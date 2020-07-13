#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <coro.h>
#include <alloca.h>
#include <assert.h>

#define coros_count 2

int curr_coro = 0;
coro_t coros[coros_count];

coro_t *coro_resched(){
    curr_coro = (curr_coro + 1) % coros_count;
    return &coros[curr_coro];
}

typedef struct {
    int *dest; 
    int *src0; 
    int src0_size;
    int *src1;
    int src1_size;
    int *it0;
    int *it1;
} func_args;

void merge(coro_t *coro, func_args *args){
    while(*args->it0 < args->src0_size){
        if(*args->it1 < args->src1_size && args->src0[*args->it0] > args->src1[*args->it1]){
            coro_yield(coro_resched());
        }
        args->dest[*args->it0 + *args->it1] = args->src0[*args->it0];
        ++*args->it0; 
    }
    coro_yield(coro_resched());
} 

int main(){
    int arr0_size, arr1_size;
    int arr0[] = {2, 3, 10, 1001};
    int arr1[] = {-2, 2, 6, 8};
    arr0_size = sizeof(arr0) / sizeof(int);
    arr1_size = sizeof(arr1) / sizeof(int);
    int result_size = arr0_size + arr1_size; 
    int result[result_size];
    int iters[] = {0, 0};
    
    func_args args0 = { result, arr0, arr0_size, arr1, arr1_size, &iters[0], &iters[1] };
    coro_init(&coros[0], (coro_fn)merge, &args0);
    func_args args1 = { result, arr1, arr1_size, arr0, arr0_size, &iters[1], &iters[0] };
    coro_init(&coros[1], (coro_fn)merge, &args1);
    coro_start(&coros[curr_coro]);
    coro_free(&coros[0]);
    coro_free(&coros[1]);
    
    for(int i = 0; i < result_size; ++i){
        printf("%d ", result[i]);
    }
    printf("\n");
    exit(0);
}