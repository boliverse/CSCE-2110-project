#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Reservation.h"
#include <vector>

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

    Node* head;

public:
    LinkedList();
    ~LinkedList();

    void insertReservation(const Reservation& reservation);
    void removeReservation(int reservationID);
    void displayReservation(int reservationID) const;
    Reservation* findReservation(int reservationID) const;

    void displayReservations() const;
    Reservation* findReservationByStudentID(int studentID) const;
    std::vector<Reservation> getAllReservations() const;
};

#endif
