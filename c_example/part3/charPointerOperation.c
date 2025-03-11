#include <stdio.h>

int main(void){

    char *name;
    char name1[20];
    name = name1;

    *name = 'h';
    *(name +1) = 'e';
    *(name +2) = 'l';
    *(name +3) = 'l';
    *(name +4) = 'o';
    *(name +5) = 'w';
    *(name +6) = '\0';
    *(name +7) = 'l';
    *(name +8) = 'o';
    *(name +9) = 'w';

    printf("%s \n", name);


    return 0;

}