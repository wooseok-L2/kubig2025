#ifndef LIST_H
#define LIST_H

#include <iostream>

class Node {
friend class List;

private:
    int data;
    Node *next;

    Node(int data, Node *next);
};

class List {
friend std::ostream& operator << (std::ostream& out, const List& rhs);
private:
    Node *ptr;
    
public:
    List();
    ~List();

    void insertFirstNode(int data);
    void insertNode(int prevdata, int data);
    void deleteNode(int data);
    
};




#endif 