#include <stdio.h>

int main(void){
    const char *str1 = "hellow";
    char str2[] = "hello";
    char str3[] = {'h', 'e', 'l', 'l', 'o', 'w', '\0'};
    char str4 = 'h';

    printf("%s \n", str1);
    printf("%s \n", str2);
    printf("%s \n", str3);
    printf("%c \n", str4);
    printf("%p \n", &str1);
    printf("%p \n", &str2);
    printf("%p \n", &str3);
    printf("%p \n", &str4);

    str2[0] = 'H';
    //str1[0] = 'H';  => compile error!!! str1 cannot change!
    printf("%s \n", str1);


    return 0;
}