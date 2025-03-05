#include <stdio.h>

int main(void){

    int kor = 3;
    int eng = 5;
    int mat = 4;
    int credits = kor+eng+mat;
    int res;
    double kscore = 3.8;
    double escore = 4.4;
    double mscore = 3.9;
    double grade=(kscore + escore + mscore)/3.0;
    
    res=credits>=10 && grade>=4.0;

    printf("total credits : %d \n", credits);
    printf("grade : %.1lf \n", grade);
    printf("res : %d \n", res);

}