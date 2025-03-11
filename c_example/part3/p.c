#include <stdio.h>
#include <stdbool.h>

// void input_nums(int *lotto_nums, int size);
// void print_nums(int *lotto_nums, int size);

// int main(void){

//     int lotto_nums[6];
//     int size = sizeof(lotto_nums)/sizeof(lotto_nums[0]);

//     input_nums(lotto_nums, size);
//     print_nums(lotto_nums, size);

//     return 0;
// }

// void input_nums(int *lotto_nums, int size){

//     int i;
//     printf("Enter 6 numbers : \n");
//     printf("But each number should be difference! \n");

//     for (i = 0; i < size; i++){
//         scanf("%d", lotto_nums+i);
        
//         while(lotto_nums[i]>=46){
//             printf("Enter different number! : ");
//             scanf("%d", lotto_nums+i);
//         }
        
//         int j = 0;
//         for (j = 0; j < i; j++){

//             while (lotto_nums[i] == lotto_nums[j]){
//                 printf("Enter different number! : ");
//                 scanf("%d", lotto_nums+i);
//             }
//         }
//     }
// }

// void print_nums(int *lotto_nums, int size){
    
//     int i;
//     printf("lotto number is : ");

//     for (i = 0; i < size; i++){
//         printf("%d  ", lotto_nums[i]);
//     }
//     printf("\n");
// }

// int main(void){
//     char str[80] = {0};

//     printf("Enter any sentence : ");
//     gets(str);
//     puts(str);
// }

int main(void){

    char ch;
    int res = 0;
    int cnt = 0;
    int sol = 0;
    int ent = 0;

    printf("enter str \n");
    while(1){
        
        
        res = scanf("%c", &ch);
        
        if (res == -1){
            
            printf("length of long string is %d \n", sol-1);
            break;
        }
        
        printf("%c", ch);
        
        cnt++;
        
        if (ch == '\n'){
            if (sol < cnt){
                
                sol = cnt;
            }
            getchar();
            cnt = 0;
        }
        
    }

    return 0;
    
}