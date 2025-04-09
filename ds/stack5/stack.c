#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void initStack(Stack *ps, int size, int elesize)
{
    // ps->parr = malloc(sizeof(int) * size);
    ps->parr = malloc(elesize * size);
    // if (ps->parr == NULL) {}
    assert(ps->parr);       // if it is true kepp running but if it is false it would be stop
    ps->elesize = elesize;
    ps->tos = 0;
    ps->size = size;
}

void cleanupStack(Stack *ps)
{
    free(ps->parr);
}

// void push(Stack *ps, int data)            // func. definition
void push(Stack *ps, const void *pdata) 
{
    
    //if ((ps->tos) == STACKSIZE) {
    // if (ps->tos == ps->size) {
    // 	fprintf(stdout, "stack is full \n");
    // 	exit(1);
    //}
    assert(ps->tos != ps->size);
    
    // ps->array[ps->tos] = data;
    // ps->parr[ps->tos] = data;  // *(ps->parr + ps->tos) = data;
    // memcpy(&ps->parr[ps->tos], pdata, ps->elesize);    // void 포인터 역참조 불가능
    memcpy((unsigned char *)ps->parr + (ps->tos * ps->elesize), pdata, ps->elesize);
    ++ps->tos;
}

void pop(Stack *ps, void *pdata)        // 리턴안쓰고 인자값 저장
{    
    assert(ps->tos != 0);
    
    --ps->tos;
    // *pre = ps->parr[ps->tos];
    // memcpy(pdata, &ps->parr[ps->tos], ps->elesize);   // void 포인터 역참조 불가능
    memcpy(pdata, (unsigned char *)ps->parr + (ps->tos * ps->elesize), ps->elesize);
    // return ps->parr[ps->tos];
}
/*
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
*/
