#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>

static Node *creatNode(int data, Node *next)  // Cannot use at main.c
{
    Node *p = malloc(sizeof(Node));
    assert(p );
    p->data = data;
    p->next = next;

    return p;
}

void initList(List *pl)
{
    // pl->ptr = malloc(sizeof(Node));
    // pl->ptr->next = NULL;
    pl->ptr = creatNode(-1, NULL);
    // assert();
    // pl->ptr->data = ???;
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

void insertFirstNode(List *pl, int data)
{
    // Node *p = malloc(sizeof(Node));
    // p->data = data;
    // p->next = pl->ptr->next;
    // pl->ptr->next = p;
    pl->ptr->next = creatNode(data, pl->ptr->next);
}

void insertNode(List *pl, int prevdata, int data)
{
    Node *p = pl->ptr->next;
    while(p ){
        if (p->data == prevdata){
            break;
        }
        p = p->next;
    }

    if (p ){
        // Node *tmp = malloc(sizeof(Node));
        // tmp->data = data;
        // tmp->next = p->next;
        // p->next = tmp;
        p->next = creatNode(data, p->next);
    }
}

void deleteNode(List *pl, int data)
{
    Node *p = pl->ptr->next;
    Node *p2 = pl->ptr;

    while(p ){
        if (p->data == data){
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

void printList(const List *pl)
{
    Node *p = pl->ptr->next;
    while (p /*!= NULL*/){
        printf("[%d, next] ", p->data);
        printf((p->next) ? ", " : "");
        p = p->next;
    }
    printf("\n");
}

