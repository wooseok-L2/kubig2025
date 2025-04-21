#include <cstdio>
#include "list.h"
#include <iostream>

int main(void){
    List list;

    // initList(&list);

    list.insertFirstNode(4);   // [4]
    std::cout << list << std::endl;
    list.insertFirstNode(3);   // [3, 4]
    std::cout << list << std::endl;
    list.insertFirstNode(1);   // [1, 3, 4]
    std::cout << list << std::endl;
    
    list.insertNode(1, 2);     // [1, 2, 3, 4]
    std::cout << list << std::endl;

    list.deleteNode(3);        // [1, 2, 4]       
    std::cout << list << std::endl;

    // cleanupList(&list);

    return 0;
}