#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void initStack(Stack *ps, int size)
{
    ps->size = size;
    ps->parr = malloc(sizeof(int) * size);
    // if (ps->parr == NULL) {}
    assert(ps->parr);       // if it is true kepp running but if it is false it would be stop
    ps->tos = 0;
}

void cleanupStack(Stack *ps)
{
    free(ps->parr);
}

void push(Stack *ps, int data)            // func. definition
{
    
    //if ((ps->tos) == STACKSIZE) {
    // if (ps->tos == ps->size) {
    // 	fprintf(stdout, "stack is full \n");
    // 	exit(1);
    //}
    assert(ps->tos != ps->size);
    
    // ps->array[ps->tos] = data;
    ps->parr[ps->tos] = data;  // *(ps->parr + ps->tos) = data;
    ++ps->tos;
}

int pop(Stack *ps)
{
    
    if ((ps->tos) == 0){
    	fprintf(stdout, "stack is empty \n");
    	exit(2);
    }
    
    assert(ps->tos != 0);
    
    // --tos;
    --ps->tos;
    
    return ps->parr[ps->tos];
}

