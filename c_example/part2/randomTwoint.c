#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(void){

    int a, b;
    double rand1, rand2;
    while(true){

        int i=0;
        i++;
        srand((unsigned int)time(NULL)+i);
        rand1 = rand() / (double)RAND_MAX*10;
        srand((unsigned int)time(NULL)+10000+i);
        rand2 = rand() / (double)RAND_MAX*10;
        
        a = rand1;
        b = rand2;
        
        printf("1 to 100 random num : %f \n", rand1);
        printf("1 to 100 random num : %f \n", rand2);
        printf("%d > %d : %s \n", a, b, a > b ? "true" : "false");
        printf("%d < %d : %s \n", a, b, a < b ? "true" : "false");
        printf("%d == %d : %s \n", a, b, a == b ? "true" : "false");
        printf("%d != %d : %s \n", a, b, a != b ? "true" : "false");
    
        if (a == b)
            break;
    }

    return 0;
}