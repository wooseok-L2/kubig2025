#include "stack.h"
#include <cstdio>
// #include <cstdlib>
#include <cassert>

Stack::Stack(int size)
{
    this->size = size;
    // this->parr = (int *)malloc(sizeof(int) * size);
    this->parr = new int[size];
    assert(this->parr);       // if it is true kepp running but if it is false it would be stop
    this->tos = 0;
}

Stack::~Stack()
{
    // free(this->parr);
    delete[] this->parr;
}

void Stack::push(int data)            // func. definition
{
    
    assert(this->tos != this->size);
    this->parr[this->tos] = data;  // *(this->parr + this->tos) = data;
    ++this->tos;
}

int Stack::pop()
{
    
    // if ((this->tos) == 0){
    // 	fprintf(stdout, "stack is empty \n");
    // 	exit(2);
    // }
    
    assert(this->tos != 0);
    
    --this->tos;
    
    return this->parr[this->tos];
}

