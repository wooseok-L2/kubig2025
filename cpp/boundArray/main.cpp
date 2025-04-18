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

    arr4 = arr1;

    arr4 == arr1;

    for (int i = arr4.lower(); i != arr4.upper(); i++){
        std::cout << arr4[i] << std::endl;
    }

    return 0;

}