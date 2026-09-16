#include "LinkedList.h"

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

void LinkedList::displayReservations() const
{
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
