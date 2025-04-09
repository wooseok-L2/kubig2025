#include <stdio.h>

int queue[100];
int rear;
int front;

void push(int data)
{
    queue[rear] = data;
    ++rear;
}
int pop(void)
{
    int i = front;

    ++front;
    
    return queue[i];
    
}

