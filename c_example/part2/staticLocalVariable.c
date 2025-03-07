#include <stdio.h>

void local(void);
void staticVar(void);
char *global = "global variable";
int local_count = 1;

int main(void){

    int i;

    printf("%s \n", global);
    for (i=0; i<3; i++){

        local();
        staticVar();
    }

    return 0;
}

void local(void){

    printf("%s \n", global);
    int count = 1;
    printf("local() fuction %d print \n", count);
    count++;
}

void staticVar(void){

    printf("%s \n", global);
    static int static_count = 1;
    printf("staticVar() function %d print \n", static_count);
    static_count++;
}
