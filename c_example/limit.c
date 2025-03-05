#include <stdio.h> //standard input/output function
#include <limits.h>

void printHello();
// int main(int argc, char* argv[]) -> 인수 받을 때
int main(void){
    
    printHello();
    printf("Hello world\n");
    printf("char_bit : %d\n", CHAR_BIT);
    printf("char_max : %d\n", CHAR_MAX);

    return 0;
} 

void printHello(){
    
    printf("Hello, world \n");

}
