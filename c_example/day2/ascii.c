#include <stdio.h>

int main(void){
    char ch = 0;

    for (int i = 0; i < 9; i++){
        
        for (int j = 0; j < 15; j++){
            
            printf("%d: %c \t", ch, ch);
            ch++;
           
        }
        printf("\n");
    }
}