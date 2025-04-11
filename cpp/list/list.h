#ifndef LIST_H
#define LIST_H

struct Node {
    int data;
    struct Node *next;
};

class List {
    Node *ptr;
    
public:
    List();
    ~List();
    
    void insertFirstNode(int data);
    void insertNode(int prevdata, int data);
    void deleteNode(int data);
    
    void printList();
};




#endif 