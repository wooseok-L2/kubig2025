// #include <cstdio>
#include "queue.h"
#include <iostream>
 
int main(void)
{
    Queue q1(10), q2(100);
    
    // q1.initQueue(3);
    // q2.initQueue(3);
    
    q1.push(100);
    q1.push(200);
    q1.push(300);
    
    std::cout << "q1 capacity : " << q1.size() << std::endl;
    std::cout << "q1 remain   : "  << q1.remain() << std::endl;

    int i = 0;
    while (!q1.isEmpty()){
        i++;
        std::cout << "q1 pop() " << i << ": " << q1.pop() << std::endl;
    }
    i = 0;
    
    // q1.pop();
    
    q2.push(900);
    q2.push(800);
    q2.push(700);
    
    // printf("q2 1st pop() : %d \n", q2.pop());
    std::cout << "q2 1st pop() : " << q2.pop() << std::endl;
    // printf("q2 2nd pop() : %d \n", q2.pop());
    std::cout << "q2 2nd pop() : " << q2.pop() << std::endl;
    // printf("q2 3rd pop() : %d \n", q2.pop());
    std::cout << "q2 3rd pop() : " << q2.pop() << std::endl;
    
    // q1.cleanupQueue();
    // q2.cleanupQueue();    
    
    return 0;
}
