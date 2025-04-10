#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void initList(List *pl)
{
    pl->ptr = malloc(sizeof(Node));
    // assert();
    // pl->ptr->data = ???;
    pl->ptr->next = NULL;
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
    Node *p = malloc(sizeof(Node));
    p->data = data;
    p->next = pl->ptr->next;
    pl->ptr->next = p;
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
        Node *tmp = malloc(sizeof(Node));
        tmp->data = data;
        tmp->next = p->next;
        p->next = tmp;
    }
    else {
        
    }
}

void deleteNode(List *pl, int data)
{
    Node *p = pl->ptr->next;
    while(p ){
        if (p->data == data){
            break;
        }
        p = p->next;
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
}

int main(void)
{
    Node *ptr;
    ptr = malloc(sizeof(Node));
    ptr->data = 1;
    ptr->next = malloc(sizeof(Node));
    ptr->next->data = 3;
    ptr->next->next = malloc(sizeof(Node));
    ptr->next->next->data = 4;
    ptr->next->next->next = NULL;

    // insert
    {
        Node *p = malloc(sizeof(Node));   
        p->data = 2;
        p->next = ptr->next;
        ptr->next = p;
    }

    // delete
    {
        Node *p = ptr->next->next;
        ptr->next->next = p->next;   // p->next->next = p->next->next->next
        free(p);
    }
        
    // traversal
    {
        Node *p = ptr;   // first node
        // printf("[");
        while (p /*!= NULL*/){
            printf("[%d, next] ", p->data);
            // if (p->next != NULL){
            //     printf(", ");
            // }
            // else{
            //     printf(" ");
            // }
            printf((p->next) ? ", " : "");
            p = p->next;
        }
    }
    printf("\n");

    // free
    {
        Node *p = ptr;
        while(p ){
            Node *tmp = p;
            p = p->next;
            free(tmp);
        }
    }

    return 0;
}