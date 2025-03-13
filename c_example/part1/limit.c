#include <stdio.h> //standard input/output function
#include <limits.h>

void printHello();
// int main(int argc, char* argv[]) -> 인수 받을 때
int main(void){
    
    printHello();
    printf("Hello world\n");
    printf("char_bit : %d\n", CHAR_BIT);
    printf("char_max : %d\n", CHAR_MAX);
    printf("INT_MIN : %d \t INT_MAX: %d \n", INT_MIN, INT_MAX);
    printf("LONG_MAX : %ld \t LONG_MAX %ld \n", LONG_MIN, LONG_MAX);

    printf("INT_MAX + 1 : %d \n", INT_MAX + 1);

    return 0;
} 

void printHello(){
    
    printf("Hello, world \n");

}
