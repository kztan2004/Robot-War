#pragma once
#include "Battlefield.h"

using namespace std;

class LinkedList
{
private:
    Node *newnode;

public:
    LinkedList();

    ~LinkedList();

    void append(Node *node, Robot *r);

    void pop(Node *node);

    Node *getNode() const;

    void setNode(Node *node);
};