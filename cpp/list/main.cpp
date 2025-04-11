#include <cstdio>
#include "list.h"
#include <iostream>

int main(void){
    List list;

    // initList(&list);

    list.insertFirstNode(4);   // [4]
    list.printList();
    list.insertFirstNode(3);   // [3, 4]
    list.printList();
    list.insertFirstNode(1);   // [1, 3, 4]
    list.printList();
    
    list.insertNode(1, 2);     // [1, 2, 3, 4]
    list.printList();

    list.deleteNode(3);        // [1, 2, 4]       
    list.printList();

    // cleanupList(&list);

    return 0;
}