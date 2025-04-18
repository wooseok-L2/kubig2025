#include <iostream>
#include "boundArray.h"

int main(){
    BoundArray arr1(1, 11);       // index : (1, 11) -> 1 ~ 10
    BoundArray arr2(10);          // index : (0, 9) -> 0 ~ 9
    BoundArray arr3;              // index : (0, 100) 
    
    for (int i = arr1.lower(); i != arr1.upper(); i++)
    {
        arr1[i] = i;
    }

    // arr1[5] = 6;    //boundary error!
    
    const BoundArray arr4 = arr1;

    arr3 = arr1;

    arr3 == arr1;

    for (int i = arr3.lower(); i != arr3.upper(); i++){
        std::cout << arr3[i] << std::endl;
    }

    return 0;

}