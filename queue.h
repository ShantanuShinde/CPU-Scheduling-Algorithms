#include "List.h"
#include<iostream>

class Queue
{
    List *queue;
    public:
    Queue();
    bool isEmpty();
    void enqueue(int data);
    int dequeue();
};
