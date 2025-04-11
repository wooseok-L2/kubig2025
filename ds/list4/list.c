#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

void initList(List *pl, int eleSize)
{
    pl->ptr = malloc(sizeof(Node) /* + eleSize*/ );
    pl->ptr->next = NULL;
    pl->eleSize = eleSize;
}

void cleanupList(List *pl)
{
    Node *p = pl->ptr;
    while(p ){
        Node *tmp = p;
        p = p->next;
        free(tmp);
    }
}

void insertFirstNode(List *pl, const void *pdata)
{
    Node *p = malloc(sizeof(Node) + pl->eleSize);
    // p->data = data;
    // memcpy((unsigned char*)p + sizeof(Node), pdata, pl->eleSize);
    memcpy(p + 1, pdata, pl->eleSize);  // 위의 식과 같음
    p->next = pl->ptr->next;
    pl->ptr->next = p;
}

void insertNode(List *pl, const void *pprevdata, const void *pdata)
{
    Node *p = pl->ptr->next;
    while(p ){
        // if (p->data == prevdata)
        if (memcmp(p + 1, pprevdata, pl->eleSize) == 0){
            break;
        }
        p = p->next;
    }

    if (p ){
        // Node *tmp = malloc(sizeof(Node));
        Node *tmp = malloc(sizeof(Node) + pl->eleSize);
        // tmp->data = data;
        memcpy(tmp + 1, pdata, pl->eleSize);
        tmp->next = p->next;
        p->next = tmp;
    }
}

void deleteNode(List *pl, const void *pdata)
{
    Node *p = pl->ptr->next;
    Node *p2 = pl->ptr;

    while(p ){
        // if (p->data == data)
        if (memcmp(p + 1, pdata, pl->eleSize) == 0){
            break;
        }
        p = p->next;
        p2 = p2->next;
    }

    if (p ){
        p2->next = p->next;
        free(p);
    }
}

void printList(const List *pl, void (*print)(const void *))
{
    Node *p = pl->ptr->next;
    while (p /*!= NULL*/){
        print(p + 1);
        printf((p->next) ? ", " : "");
        p = p->next;
    }
    printf("\n");
}

