#include "WaitingList.h"

// MISTAKE: WaitingList.cpp used cout and endl, but WaitingList.h includes
// nothing at all and this file had no <iostream> and no "using namespace std".
// It only avoided an error earlier because nothing was compiling this far.
#include <iostream>

using namespace std;

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
        // MISTAKE (small): this returned silently so the user got no feedback
        // when the line was already empty.
        cout << "The waiting list is already empty." << endl;
        return;
    }

    cout << "Student ID " << front->studentID
         << " has been removed from the waiting list." << endl;

    Node* temp = front;
    front = front->next;
    delete temp;

    if(front == nullptr)
    {
        rear = nullptr;
    }
}

bool WaitingList::isEmpty() const
{
    return front == nullptr;
}

void WaitingList::display() const
{
    if(front == nullptr)
    {
        cout << "The waiting list is empty." << endl;
        return;
    }

    Node* current = front;

    while(current != nullptr)
    {
        cout << "Student ID: " << current->studentID << endl;
        current = current->next;
    }
}
