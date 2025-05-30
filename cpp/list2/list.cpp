#include <cstdio>
// #include <stdlib.h>
#include "list.h"
#include <cassert>
#include <iostream>

// static Node *creatNode(int data, Node *next)  // Cannot use at main.c
// {
//     Node *p = new Node;
//     assert(p );
//     p->data = data;
//     p->next = next;

//     return p;
// }

List::List()
{
    // pl->ptr = malloc(sizeof(Node));
    // pl->ptr->next = NULL;
    this->ptr = new Node(-1, NULL);
    // assert();
    // pl->ptr->data = ???;
}

List::~List()
{
    Node *p = this->ptr;
    while(p ){
        Node *tmp = p;
        p = p->next;
        delete tmp;
    }
}

void List::insertFirstNode(int data)
{
    // Node *p = malloc(sizeof(Node));
    // p->data = data;
    // p->next = pl->ptr->next;
    // pl->ptr->next = p;
    this->ptr->next = new Node(data, this->ptr->next);
}

void List::insertNode(int prevdata, int data)
{
    Node *p = this->ptr->next;
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
        p->next = new Node(data, p->next);
    }
}

void List::deleteNode(int data)
{
    Node *p = this->ptr->next;
    Node *p2 = this->ptr;

    while(p ){
        if (p->data == data){
            break;
        }
        p = p->next;
        p2 = p2->next;
    }

    if (p ){
        p2->next = p->next;
        delete p;
    }
}

Node::Node(int data, Node *next)
{
    this->data = data;
    this->next = next;
}

std::ostream& operator << (std::ostream& out, const List& rhs)
{
    Node *p = rhs.ptr->next;
    out << "[";
    while (p /*!= NULL*/){
        // printf("[%d, next] ", p->data);
        out << p->data;
        // printf((p->next) ? ", " : "");
        out << ((p->next) ? ", " : "");
        p = p->next;
    }
    // printf("\n");
    out << "]";

    return out;
}

