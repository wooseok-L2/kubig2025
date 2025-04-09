#include <stdio.h>

/*
void my_strcpy(char *des, const char *src)
{
    int i;
    for (i = 0; src[i]; i++) {
    	des[i] = src[i];
    }
    des[i] = '\0';
}
*/

void my_strcpy(char *des, const char *src)
{
/*
    while (*src) {
    	*des++ = *src++;
    }
    *des = '\0';
*/
    while (*des++ = *src++)
        ;
}

int main(void)
{
    char str1[100];
    char *str2 = "hello, world";
    
    my_strcpy(str1, str2);
    printf("str1: %s \n", str1);
    
    return 0;
}
