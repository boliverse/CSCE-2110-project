#include "LinkedList.h"

// MISTAKE: this file used cout and endl but nothing included <iostream>.
// LinkedList.h only includes <string> through Reservation.h.
#include <iostream>

using namespace std;

LinkedList::LinkedList()
{
    head = nullptr;
}

LinkedList::~LinkedList()
{
    Node* current = head;
    while(current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
}

void LinkedList::insertReservation(const Reservation& reservation)
{
    Node* newNode = new Node(reservation);

    if(head == nullptr)
    {
        head = newNode;
        return;
    }

    Node* current = head;

    while(current->next != nullptr)
    {
        current = current->next;
    }

    current->next = newNode;
}

void LinkedList::removeReservation(int reservationID)
{
    if(head == nullptr)
    {
        return;
    }

    if(head->reservation.getReservationID() == reservationID)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;

    while(current->next != nullptr)
    {
        if(current->next->reservation.getReservationID() == reservationID)
        {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return;
        }

        current = current->next;
    }
}

void LinkedList::displayReservation(int reservationID) const
{
    Node* current = head;

    while(current != nullptr)
    {
        if(current->reservation.getReservationID() == reservationID)
        {
            current->reservation.display();
            return;
        }

        current = current->next;
    }

    cout << "Reservation not found." << endl;
}

// new function, prints every reservation in the list
void LinkedList::displayReservations() const
{
    if(head == nullptr)
    {
        cout << "There are no active reservations." << endl;
        return;
    }

    Node* current = head;

    while(current != nullptr)
    {
        current->reservation.display();
        current = current->next;
    }
}

Reservation* LinkedList::findReservation(int reservationID) const
{
    Node* current = head;

    while(current != nullptr)
    {
        if(current->reservation.getReservationID() == reservationID)
        {
            return &current->reservation;
        }

        current = current->next;
    }

    return nullptr;
}

// new function, returns the first reservation that belongs to this student
Reservation* LinkedList::findReservationByStudentID(int studentID) const
{
    Node* current = head;

    while(current != nullptr)
    {
        if(current->reservation.getStudentID() == studentID)
        {
            return &current->reservation;
        }

        current = current->next;
    }

    return nullptr;
}
