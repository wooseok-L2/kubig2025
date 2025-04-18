#include <iostream>
#include "safeArray.h"

int main(){
    SafeArray arr1;
    SafeArray arr2(10);
    int nums[] = {1, 2, 3, 4, 5};
    SafeArray arr3(nums, 5);
    SafeArray arr4 = arr3;

    arr1 = arr3;

    arr1 == arr3;

    for (int i = 0; i < arr1.size(); i++)
    {
        std::cout << arr1[i] << std::endl;
    }

    // arr1[5] = 6;    //boundary error!
    
    Array *p = new SafeArray(nums, 5);

    (*p)[5] = 6;       // p->operator[](5) = 6;

    delete p;

    return 0;

}