#include "string.h"


int main(void){

    char *str = "wonderful C class";
    int len = my_strlen(str);
    printf("len of str : %d \n", len);

    char str2[40];
    strcpy(str2, str);
    printf("%s \n", str2);

    if (strcmp(str2, str) == 0){
        printf("str2 and str are same \n");
    }
    else{
        printf("str2 and str are different \n");
    }

    my_strcat(str2, "----");
    my_strcat(str2, str);
    printf("%s \n", str2);

    return 0;
}