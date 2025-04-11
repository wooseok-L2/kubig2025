#ifndef LIST_H
#define LIST_H

typedef struct node {
    // int data;
    struct node *next;
} Node;

typedef struct list {
    Node *ptr;
    int eleSize;
} List;


void initList(List *pl, int eleSize);
void cleanupList(List *pl);

void insertFirstNode(List *pl, const void *pdata);
void insertNode(List *pl, const void *pprevdata, const void *pdata);
void deleteNode(List *pl, const void *pdata);

void printList(const List *pl, void (*print)(const void *));

#endif 