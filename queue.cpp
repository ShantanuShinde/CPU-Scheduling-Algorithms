#include "queue.h"


Queue::Queue()
{
    queue = new List;
    queue->head = NULL;
    queue->tail = NULL;
}

bool Queue::isEmpty()
{
    return queue->head ==NULL;
}

void Queue::enqueue(int data)
{
    queue->InsertInTail(data);
}

int Queue::dequeue()
{
    return queue->Remove();
}

