#include <stdio.h>
#include "list.h"

void printInt(const void *pdata)
{
    printf("%d", *(int *)pdata);
}

void printDouble(const void *pdata)
{
    printf("%f", *(double *)pdata);
}

int main(void){
    List list1, list2;
    initList(&list1, sizeof(int));
    initList(&list2, sizeof(double));

    int i = 4;    insertFirstNode(&list1, &i);        // [4]
    i = 3;        insertFirstNode(&list1, &i);        // [3, 4]
    i = 1;        insertFirstNode(&list1, &i);        // [1, 3, 4]

    int j = 1;    
    i = 2;        insertNode(&list1, &j, &i);         // [1, 2, 3, 4]
    i = 3;        deleteNode(&list1, &i);             // [1, 2, 4]      
    
    printList(&list1, printInt);

    double d = 4.4;    insertFirstNode(&list2, &d);   // [4.4]
    d = 3.3;        insertFirstNode(&list2, &d);      // [3.3, 4.4]
    d = 1.1;        insertFirstNode(&list2, &d);      // [1.1, 3.3, 4.4]

    double f = 1.1;    
    d = 2.2;        insertNode(&list2, &f, &d);       // [1.1, 2.2, 3.3, 4.4]
    d = 3.3;        deleteNode(&list2, &d);           // [1.1, 2.2, 4.4]      
    
    printList(&list2, printDouble);

    cleanupList(&list1);
    cleanupList(&list2);

    return 0;
}