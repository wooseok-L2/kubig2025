#include <stdio.h>
#include "queue.h"
 
int main(void)
{
    Queue q1, q2;
    
    initQueue(&q1, 3, sizeof(int));
    initQueue(&q2, 3, sizeof(int));
    
    int i;
    
    i = 100; push(&q1, &i);
    i = 200; push(&q1, &i);
    i = 300; push(&q1, &i);
    
    int re;
    printf("q1 1st pop() : %d \n", pop(&q1));
    printf("q1 2nd pop() : %d \n", pop(&q1));
    printf("q1 3rd pop() : %d \n", pop(&q1));
    
    // pop(&q1);
    
    double d;
    
    d = 1.1; push(&q2, 700);
    d = 1.2; push(&q2, 800);
    d = 1.3; push(&q2, 900);
    
    printf("q2 1st pop() : %f \n", pop(&q2));
    printf("q2 2nd pop() : %f \n", pop(&q2));
    printf("q2 3rd pop() : %f \n", pop(&q2));
    
    
    return 0;
}
