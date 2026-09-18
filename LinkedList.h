#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Reservation.h"

using namespace std;

class LinkedList
{
private:
    struct Node
    {
        Reservation reservation;
        Node* next;

        Node(const Reservation& r) : reservation(r), next(nullptr) {}
    };
public:
    LinkedList();
    ~LinkedList();

    void insertReservation(const Reservation& reservation);
    void removeReservation(int reservationID);
    void displayReservation(int reservationID) const;
    Reservation* findReservation(int reservationID) const;
};
#endif
