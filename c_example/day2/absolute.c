#include <stdio.h>
#include <stdbool.h>

// standard
// int main(void){

//     int num;
//     printf("Enter number :");
//     scanf("%d", &num);

//     if(num < 0){
//         num = - num;
//     }
//     printf("absolute number is %d \n", num);

//     return 0;
// }

// use bool
int main(void){

    int num;
    int state;

    printf("Enter number :");
    scanf("%d", &num);

    if(num < 0){
        state = false;
    }
    else{
        state = true;
    }

    num = state ? num : -num;
    
    printf("absolute number is %d \n", num);

    return 0;
}