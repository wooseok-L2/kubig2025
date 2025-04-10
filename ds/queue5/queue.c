#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void initQueue(Queue *pq, int size, int elesize)
{
    pq->front = 0;
    pq->rear = 0;
    pq->size = size;
    pq->elesize = elesize;
    pq->parr = malloc(size * elesize);
    assert(pq->parr != 0);
}

void cleanupQueue(Queue *pq)
{
    free(pq->parr);
}

void push(Queue *pq, const void *pdata)
{
    // pq->array[pq->rear] = data;
    
    if ((pq->rear) == pq->size){
    	fprintf(stdout, "Queue is full \n");
    	exit(2);
    }
    
    // assert(pq->rear != pq->size);
    memcpy((unsigned char *)pq->parr + (pq->rear * pq->elesize), pdata, pq->elesize);
    // pq->parr[pq->rear] = data;
    ++pq->rear;
}

void pop(Queue *pq, void *pdata)
{
    if ((pq->front) == pq->size){
    	fprintf(stdout, "Queue is empty \n");
    	exit(2);
    }
    
    // assert(pq->front != pq->size);
    
    int i = pq->front;

    memcpy(pdata, (unsigned char *)pq->parr + (i * pq->elesize), pq->elesize);

    ++(pq->front);
    
   // return pq->parr[i];
    
}

