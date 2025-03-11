#include <stdio.h>
#include <string.h>

int main(void){
    
    const char *str1 = "hello, world";
    char str2[] = "stack char array";
    int str1len = strlen(str1);
    int str2len = strlen(str2);

    printf("str1len : %d, str2len : %d \n", str1len, str2len);

    char str3[20];
    strcpy(str3, str1);
    str3[0] = 'H';
    printf("%d \n", str1[5]);
    
    printf("%ld \n", sizeof(str1));

    if (strcmp(str1, str3) == 0){
        printf("str1 and str2 are same \n");
    }
    else{
        printf("difference %d \n", strcmp(str1, str3));
    }

    strcat(str3, str2);
    printf("%s \n", str3);

    return 0;
}