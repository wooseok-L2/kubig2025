#include <stdio.h>

/*int main(void){

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

}*/

/*int main(void){

    int res;
    
    res = (sizeof(short) > sizeof(long)) ? 1 : 0;
    printf("%s \n", sizeof(short)>sizeof(long) ? "short" : "long");

    return 0;
}*/

// int main(void){

//     int seat = 70;
//     int visitor = 65;
//     double rate;

//     rate = (double)visitor/(double) seat*100;

//     printf("rate : %.2lf%% \n", rate);

//     return 0;
// }

// int main(void){

//     int hour, min, sec;
//     double time;
//     double temp_min;
    
//     print("Enter hour : \n");
//     scanf("%.2lf", &time);

//     temp_min = time * 6;

//     hour = temp_time / 60;

//     min = temp_time % 60;

//     sec = ((temp_time - hour*60)-min);

//     return 0;
// }

// 

// int main(void){

//     double kg;
//     double cm;
//     double bmi;

//     printf("Enter weight and height : ");
//     scanf("%lf %lf", &kg, &cm);

//     bmi = kg/((cm/100)*(cm/100));

//     printf("bmi is %.2lf, %s \n", bmi, (20<=bmi && bmi<25) ? "standard" : "manage your weight");

//     return 0;

// }

// int main(void){
    
//     printf("It is calculator for integer\n");
//     printf("Enter the integer \n");
    
//     int a;
//     int b;
//     char c;
//     int res;
    
//     scanf("%d %c %d", &a, &c, &b);
    
//     if(c=='+'){
//         res = a + b;
//     } 
//     else if(c=='-'){
//         res = a - b;
//     } 
//     else if(c=='*'){
//         res = a * b;
//     } 
//     else if(c=='/'){
//         res = a / b;
//     } 
//     else if(c=='%'){
//         res = a % b;
//     } 
//     else{
//         printf("Try again");
//     }
    
//     printf("%d %c %d = %d \n", a, c, b, res);

//     return 0;
// }