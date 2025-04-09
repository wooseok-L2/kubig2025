#include <stdio.h>

int stack[100];       // global
int tos;                // top of stack

void push(int data)
{
    stack[tos] = data;
    tos++;
}

int pop(void)
{
    --tos;
    return stack[tos];
}

int main(void)
{
    push(100);
    push(200);
    push(300);
    
    int re = pop(); printf("1st pop() : %d\n", re);
    re = pop();     printf("2nd pop() : %d\n", re);
    re = pop();     printf("3rd pop() : %d\n", re);
    
    return 0;
}
