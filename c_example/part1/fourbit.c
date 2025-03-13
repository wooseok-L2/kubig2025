#include <stdio.h>
#define BOLD 0x01
#define ITALIC (0x01<<1) // 0x02
#define SHADOW (0x01<<2) // 0x04
#define UL     (0x01<<3) // 0x08

void printAttrib(unsigned char attr);

int main(void){

    unsigned char attr;
    attr = attr ^ attr;
    attr = attr | BOLD;
    printAttrib(attr);
    attr = attr | (ITALIC | SHADOW);
    printAttrib(attr);
    attr = attr &(~BOLD);
    printAttrib(attr);

    return 0;
}


// void printAttrib(unsigned char attr)
// {
//     printf("BOLD: %d \n", !(~(attr|~BOLD)));
//     printf("ITALIC: %d \n", !(~(attr|~ITALIC)>>1));
//     printf("SHADOW: %d \n", !(~(attr|~SHADOW)>>2));
//     printf("UL: %d \n", !(~(attr|~UL)>>3));
//     printf("-------------------------- \n");
// }

void printAttrib(unsigned char attr)
{
    printf("BOLD: %d \n", (attr&BOLD));
    printf("ITALIC: %d \n", (attr&ITALIC)>>1);
    printf("SHADOW: %d \n", ((attr&SHADOW)>>2));
    printf("UL: %d \n", (attr&UL)>>3);
    printf("-------------------------- \n");
}


