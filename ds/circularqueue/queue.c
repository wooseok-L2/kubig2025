#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void initQueue(Queue *pq, int size)
{
    pq->front = 0;
    pq->rear = 0;
    pq->size = size;
    pq->parr = malloc(size * sizeof(int));
    assert(pq->parr );       // 디버깅모드에서만 작동  assert(pq->parr != 0);   릴리즈 모드에서는 assert 함수 사라짐
}

void cleanupQueue(Queue *pq)
{
    free(pq->parr);
}

void push(Queue *pq, int data)
{
    // pq->array[pq->rear] = data;
    
    // if ((pq->rear) == pq->size){
    // 	fprintf(stdout, "Queue is full \n");
    // 	exit(2);
    // }
    
    assert((pq->rear + 1) % pq->size != pq->front);
    
    pq->parr[pq->rear] = data;
    // ++pq->rear;
    pq->rear = (pq->rear + 1) % pq->size;
}

int pop(Queue *pq)
{
    if ((pq->rear) == pq->front){
    	fprintf(stdout, "Queue is empty \n");
    	exit(2);
    }
    
    // assert(pq->rear != pq->front);
    
    int i = pq->front;

    // ++(pq->front);
    pq->front = (pq->front + 1) % pq->size;
    
    return pq->parr[i];
    
}

