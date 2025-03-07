#include <stdio.h>

// int main(void){

//     char str;

//     printf("Enter one letter :");
//     scanf("%c", &str);

//     printf("%c is %s \n", str, str>91 ? "Lower" : "Upper");

//     return 0;
// }

int main(void){

    char str;

    printf("Enter Alphabet :");
    scanf("%c", &str);

    if ('A' <= str && str <= 'Z'){
        printf("%c is %s \n", str, "Upper");
    }
    else if('a' <= str && str <= 'z'){
        printf("%c is %s \n", str, "Lower");
    }
    else{
        printf("This is not Alphabet \n");
    }

    return 0;
}