#include <stdio.h>

int main(void){

    FILE *a;

    a = fopen("test.dat", "w");

    if (a == NULL){
        printf("can't open file \n");

        return 1;
    }

    fprintf(a, "it is example date as file to save \n");
    fclose(a);

    return 0;
}