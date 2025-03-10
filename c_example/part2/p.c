#include <stdio.h>
#include <stdlib.h>

// int main(void){

//     int i;
    
//     for(i=0; i<10; i++){

//         printf("$");

//     }
//     printf("\n");

//     return 0;
// }

// int main(void){

//     int i;
//     int j;

//     for(i=0; i<5; i++){

//         for(j=0; j<5; j++){

//             if(i+j==4 || i==j){
//                 printf("*");
//             }
//             else{
//                 printf(" ");
//             }
//         }
//         printf("\n");
//     }
//     return 0;
// // }

// int main(void){
//     int num;
//     int np;
//     int cnt = 0;

//     printf("Enter num :");
//     scanf("%d", &num);

//     for (int i = 2; i < num; i++){
//         np = 1;
//         for(int j = 2; j < i; j++){

//             if(i % j == 0){
//                 np = 0;
//                 break;
//             }
//         }
        
//         if (np == 1){
//             printf("%5d", i);
//             cnt++;
//         }   
        
//         if (cnt == 5){
//             printf("\n");
//             cnt = 0;
//         }
//     }
//     printf("\n");
// }

// }

// int main(void){
//     int num;
//     int np;
//     int cnt = 0;

//     printf("Enter num :");
//     scanf("%d", &num);

//     int i =2;
//     while (i < num){
//         np = 1;
//         for(int j = 2; j < i; j++){

//             if(i % j == 0){
//                 np = 0;
//                 break;
//             }
//         }
        
//         if (np == 1){
//             printf("%d \t", i);
//             cnt++;
//         }   
        
//         if (cnt == 5){
//             printf("\n");
//             cnt = 0;
//         }
//         i++;
//     }
//     printf("\n");
// }

// int main(void){
//     int a, b;
//     double rand1, rand2;
    
//     srand((unsigned int)time(NULL));
//     rand1 = (double)RAND_MAX;
//     srand((unsigned int)time(NULL));
//     rand2 = rand()/(double)RAND_MAX;

//     printf(" %f, %f \n", rand1, rand2);

        
//         a = rand1;
//         b = rand2;

//         return 0;
// }

// void sum(int x);

// int main(void){

//     sum(10);
//     sum(100);

//     return 0;
// }

// void sum(int x){

//     int i;
//     int res = 0;

//     for (i=1; i<x+1; i++){

//         res += i;
//     }

//     printf("sum(1 to num) : %d \n", res);

//     return;
// }

int rec_func(int n);

int main(void){

    int res;
    res = rec_func(10);

    printf("%d \n", res);

    return 0;
}

int rec_func(int n){
    int res;
    
    if (n == 0) return 1;
    else{
        res = n + rec_func(n-1);
    }

    return res;
}