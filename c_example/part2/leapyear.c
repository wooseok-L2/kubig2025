#include <stdio.h>
#include <stdbool.h>

int main(void){

    int year;

    while(true){
        printf("Enter Year : ");
        scanf("%d", &year);

        if (!year){

            printf("exit \n");
            break;
        }
        
        // if (year % 4 == 0){
                
        //     printf("%d year is leap year. \n", year);
        // }
        // else{
                
        //     printf("%d year is normal year.\n", year);
        // } 
       
        printf("%d year is %s. \n", year, year%4 ? "normal" : "leap");
        printf("Enter 0 for exit \n");
            
    }

    return 0;
}