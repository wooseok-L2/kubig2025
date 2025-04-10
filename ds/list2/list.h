#ifndef LIST_H
#define LIST_H

typedef struct node {
    int data;
    struct Node *next;
} Node;

typedef struct list {
    Node *ptr;
} List;


void initList(List *pl);
void cleanupList(List *pl);

void insertFirstNode(List *pl, int data);
void insertNode(List *pl, int prevdata, int data);
void deleteNode(List *pl, int data);

void printList(const List *pl);

#endif 