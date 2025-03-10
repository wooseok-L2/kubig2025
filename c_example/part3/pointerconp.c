#include <stdio.h>

int main(void){
    int var_a, var_b;
    int *pVar;

    var_a = 100;
    pVar = &var_b;
    *pVar = 200;
    
    printf("var_a : %d, &var_a :%p \n", var_a, &var_a);
    printf("*pVar : %d, pVar : %p \n", *pVar, pVar);
    printf("pointer size : %ld\n", sizeof(pVar));

    return 0;

}