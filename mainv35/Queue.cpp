#include "Queue.h"

Queue::Queue(int c)
{
    size = 0;
    capacity = c;
    front = -1;
    back = -1;
    queue = new Robot *[capacity];
}

Queue::~Queue()
{
    delete[] queue;
}

void Queue::push(Robot *val)
{
    if (isFull())
    {
        cout << "queue full" << endl;
        return;
    }
    if (size == 0)
    {
        front = 0;
        back = 0;
        queue[back] = val;
    }
    else
    {
        back = (back + 1) % capacity;
        queue[back] = val;
    }
    size++;
}

void Queue::pop()
{
    if (isEmpty())
    {
        cout << "queue empty" << endl;
        return;
    }
    front = (front + 1) % capacity;
    size--;
}

Robot *Queue::Front()
{
    if (isEmpty())
    {
        return NULL;
    }
    return queue[front];
}

bool Queue::isFull() const { return size == capacity; }
bool Queue::isEmpty() const { return size == 0; }
