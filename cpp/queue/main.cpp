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
    
    // printf("q1 1st pop() : %d \n", q1.pop());
    std::cout << "q1 1st pop() : " <<  q1.pop() << std::endl;    // cout 반환
    // printf("q1 2nd pop() : %d \n", q1.pop());
    std::cout << "q1 2nd pop() : " <<  q1.pop() << std::endl;
    // printf("q1 3rd pop() : %d \n", q1.pop());
    std::cout << "q1 3rd pop() : " <<  q1.pop() << std::endl;
    
    // q1.pop();
    
    q2.push(700);
    q2.push(800);
    q2.push(900);
    
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
