#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

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