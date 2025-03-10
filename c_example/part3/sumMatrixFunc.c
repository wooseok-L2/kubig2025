#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sumMatrix(int (*pm)[3], int n, int m);

int main(void){

    int matrix[4][3] = {{1, 2, 3},
                       {11, 12, 13},
                       {21, 22, 23},
                       {21, 22, 23}};
    
    int sum = sumMatrix(matrix, (sizeof(matrix)/sizeof(int))/(sizeof(matrix[0])/sizeof(int)),
    (sizeof(matrix[0])/sizeof(int)));

    printf("sum of matrix : %d \n", sum);

    return 0;   
}

int sumMatrix(int (*pm)[3], int n, int m){

    int sum = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            sum += pm[i][j];
        }
    }
    
    return sum;
}