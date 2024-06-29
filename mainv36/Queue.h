#pragma once
#include <iostream>

using namespace std;

class Robot;

class Queue
{
private:
    Robot **queue;
    int capacity;
    int size;
    int front;
    int back;

public:
    Queue(int c);

    ~Queue();

    void push(Robot *val);

    void pop();

    Robot *Front();

    bool isFull() const;

    bool isEmpty() const;
};