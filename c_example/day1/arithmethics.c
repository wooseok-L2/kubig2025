# include <stdio.h>

int main(void){

    int a, b;
    printf("Input a, b :");
    scanf("%d %d", &a, &b);

    printf("PLUS %d + %d = %d \n", a, b, a+b);
    printf("MINUS %d - %d = %d \n", a, b, a-b);
    printf("MULTIPLY %d * %d = %d \n", a, b, a*b);
    printf("DIVISION %d / %d = %d \n", a, b, a/b);
    printf("NAMUGI %d NAMUGI %d = %d \n", a, b, a%b);
    
}