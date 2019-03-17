#include "List.h"
#include<iostream>

List::List()
{
    head = NULL;
    tail = NULL;
}

void List::InsertInTail(int data)
{
    if(head==NULL)
    {
        head = tail = new Node;
        head->next = NULL;
        head->data = data;
    }
    else{
        Node *temp = new Node;
        temp->data = data;
        tail->next = temp;
        tail = tail->next;
        tail->next = NULL;
    }
}

void List::InsertInHead(int data)
{
    if(head==NULL)
    {
        head = tail = new Node;
        head->next = NULL;
        head->data = data;
    }
    else
    {
        Node *temp = new Node;
        temp->data = data;
        temp->next = head;
        head = temp;
    }
}

int List::Remove()
{
    if(head==NULL)
    {
        return -1;
    }
    Node *temp = head;
    if(head->next==NULL)
    {
        head = NULL;
        return temp->data;
    }
    head = head->next;
    int t = temp->data;
    delete temp;
    return t;
}