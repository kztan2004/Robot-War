#include "LinkedList.h"

LinkedList::LinkedList()
{
    newnode = new Node;
    newnode->r = nullptr;
    newnode->next = nullptr;
}

LinkedList::~LinkedList()
{
    if (newnode->r == nullptr)
    {
        delete newnode;
        newnode = nullptr;
    }
    else
    {
        Node *ptr = newnode;
        Node *nextptr;
        do
        {
            nextptr = ptr->next;
            delete ptr->r;
            delete ptr;
            ptr = nextptr;
        } while (ptr != newnode);
        newnode = nullptr;
    }
}

void LinkedList::append(Node *node, Robot *r)
{
    Node *newNode = new Node;
    newNode->r = r;
    newNode->next = nullptr;
    if (node->r == nullptr)
    {
        node->r = newNode->r;
        node->next = node;
    }
    else
    {
        Node *ptr = node;
        while (ptr->next != node)
        {
            ptr = ptr->next;
        }
        ptr->next = newNode;
        newNode->next = node;
    }
}

void LinkedList::pop(Node *node)
{
    Node *ptr = node;
    Node *ptr2 = ptr->next->next;
    if (ptr->next->r->getStatus()) // deallocate memory when robot completely dead
        delete ptr->next->r;
    delete ptr->next;
    ptr->next = ptr2;
}

void LinkedList::setNode(Node *node) { newnode = node; }

Node *LinkedList::getNode() const { return newnode; }
