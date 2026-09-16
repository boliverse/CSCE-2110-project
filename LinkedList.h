#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Reservation.h"

using namespace std;

class LinkedList
{

    private:
        void InsertReservation(Reservation r1);
        void RemoveReservation(Reservation r1);
        void DisplayReservation(Reservation r1);
        Reservation FindReservation(Reservation r1);
};
#endif
