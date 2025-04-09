#include <stdio.h>  // /usr/include/
#include "stack.h"  // /ds/stack3/  => same directory

int main(void)
{

    Stack s1, s2;

    initStack(&s1, 10, sizeof(int));
    initStack(&s2, 100, sizeof(double));
    
    int i;
    i = 100; push(&s1, &i);
    i = 200; push(&s1, &i);
    i = 300; push(&s1, &i);
    
    int re;
    pop(&s1, &re);  printf("s1 1st pop() : %d \n", re);
    pop(&s1, &re);  printf("s1 2nd pop() : %d \n", re);
    pop(&s1, &re);  printf("s1 3rd pop() : %d \n", re);
    
    double d;
    d = 1.1; push(&s2, &d);
    d = 1.2; push(&s2, &d);
    d = 1.3; push(&s2, &d);
    
    double re2;
    pop(&s2, &re2);  printf("s2 1st pop() : %f \n", re2);
    pop(&s2, &re2);  printf("s2 2nd pop() : %f \n", re2);
    pop(&s2, &re2);  printf("s2 3rd pop() : %f \n", re2);
    
    cleanupStack(&s1);
    cleanupStack(&s2);
    
    return 0;
}





