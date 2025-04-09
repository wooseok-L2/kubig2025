#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

// int stack[100];
// int tos;

// int stack2[100];
// int tos2;

// int stack3[100];
// int tos3;

void push(Stack *ps, int data)            // func. definition
{
    // stack[tos] = data;
    // tos++;
    // (*ps).array[(*ps).tos] = data;
    ps->array[ps->tos] = data;
    ++(*ps).tos;
    // ++ps->tos;
    
    if ((ps->tos) == STACKSIZE) {
    	fprintf(stdout, "stack is full \n");
    	// fprintf(stderr, "stack is full \n");
    	exit(1);
    }
}

int pop(Stack *ps)
{
    // --tos;
    --(*ps).tos;
    
    if ((ps->tos) == 0){
    	fprintf(stdout, "stack is empty \n");
    	// fprintf(stderr, "stack is empty \n");
    	exit(2);
    }
    
    return (*ps).array[(*ps).tos];
}

void initStack(Stack *ps)
{
    ps->tos = 0;
    // (*ps).tos = 0;
}
