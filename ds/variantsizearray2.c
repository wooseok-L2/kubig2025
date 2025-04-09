#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int size;
    scanf("%d", &size);
    
    // int array[size];    //c99  it is accepted from 1999
    
    int *parr = (int *)malloc(sizeof(int) * size);
    
    // if ( parr == 0) printf("malloc didnt have space \n");
    
    for (int i = 0; i < size; i++){
        *(parr + i) = i + 1;
        // parr[i] = i + 1;
    }
    
    for (int i = 0; i < size; i++){
        printf("%d ", *(parr + i));
        // printf("%d ", parr[i]);
    }
    
    printf("\n");
    
    free(parr);
    
    return 0;
}
