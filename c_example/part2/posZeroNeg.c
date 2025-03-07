#include <stdio.h>
#include <stdlib.h>

// int main(int argc, char* argv[]){

//     char* res;
//     int num = atoi(argv[1]);

//     if(argc < 2){
        
//         printf("Enter values");    
//         return 0;
//     }

//     if (num == 0) {
//         res = "Zero";
//     }else if(num < 0){
//         res = "Negative";
//     }else{
//         res = "Positive";
//     }

//     printf("%d is %s \n", num, res);
// }

// int main(void){

//     int num;
//     char* str;

//     printf("Enter number : ");
//     scanf("%d", &num);

//     if (num > 0){
//         str="Positive";
//     }
//     else if(num < 0){
//         str="Negative";
//     }
//     else{
//         str = "Negative";
//     }
//     printf("%d is %s \n", num, str);

//     return 0;
// }

int main(void){
    int num;

    printf("Enter number : ");
    scanf("%d", &num);

    printf("%d is %s. \n", num, num>0 ? "Positive" : num<0 ? "Negative" : "Zero");

}