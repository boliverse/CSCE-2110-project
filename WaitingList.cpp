#include "WaitingList.h"

WaitingList::WaitingList()
{
    front = nullptr;
    rear = nullptr;
}

WaitingList::~WaitingList()
{
    while(front != nullptr)
    {
        Node* temp = front;
        front = front->next;
        delete temp;
    }

    rear = nullptr;
}

void WaitingList::queue(int studentID)
{
    Node* newNode = new Node(studentID);

    if(rear == nullptr)
    {
        front = newNode;
        rear = newNode;
        return;
    }

    rear->next = newNode;
    rear = newNode;
}

void WaitingList::dequeue()
{
    if(front == nullptr)
    {
        return;
    }

    Node* temp = front;
    front = front->next;
    delete temp;

    if(front == nullptr)
    {
        rear = nullptr;
    }
}

void WaitingList::display() const
{
    Node* current = front;

    while(current != nullptr)
    {
        cout << "Student ID: " << current->studentID << endl;
        current = current->next;
    }
}
