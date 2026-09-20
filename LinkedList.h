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

    // MISTAKE: this was the big one. The Node struct was declared but the list
    // never actually had a head pointer member. Every function in LinkedList.cpp
    // used "head", so the whole file failed with "'head' was not declared in
    // this scope". Adding the member fixes all of those errors at once.
    Node* head;

public:
    LinkedList();
    ~LinkedList();

    void insertReservation(const Reservation& reservation);
    void removeReservation(int reservationID);
    void displayReservation(int reservationID) const;
    Reservation* findReservation(int reservationID) const;

    // MISTAKE: ReservationManager called reservations.displayReservations()
    // (plural) but the list only had displayReservation(int) (singular), so it
    // did not compile. Added the plural version that prints the whole list.
    void displayReservations() const;

    // MISTAKE: ReservationManager::searchReservationByStudentID just returned
    // nullptr forever. It needs a real search in the list to work, so that
    // search lives here.
    Reservation* findReservationByStudentID(int studentID) const;
};

#endif
