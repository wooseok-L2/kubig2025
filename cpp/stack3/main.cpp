#include <iostream>
#include "mystack.h"

int main(){

    // int nums[] = {1, 2, 3, 4, 5};
    Stack s1(10);
    Stack s2;            //Stack s2(100);
    // Stack s3 = s2;

    s1.push(100);
    s1.push(200);
    s1.push(300);

    std::cout << "s1 capacity : " << s1.size() << std::endl;
    std::cout << "s1 remain   : "  << s1.remain() << std::endl;

    while (s1.isEmpty()){
        std::cout << s1.pop() << std::endl;
    }




    return 0;
}