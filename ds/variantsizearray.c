#include <stdio.h>

int main(void)
{
    int size;
    scanf("%d", &size);
    
    int array[size];    //c99  it is accepted from 1999
    
    for (int i = 0; i < size; i++){
        array[i] = i + 1;
    }
    
    for (int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
    
    printf("\n");
    
    return 0;
}
