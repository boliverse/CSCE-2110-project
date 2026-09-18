#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "Reservation.h"
#include "LinkedList.h"
#include "CancellationHistory.h"

class ReservationManager
{
private:
    LinkedList reservations;
    CancellationHistory cancellationHistory;

public:
    bool createReservation(const Reservation& reservation);
    bool cancelReservation(int reservationID);
    bool undoCancellation();

    void displayReservations() const;

    Reservation* searchReservationByID(int reservationID);

    bool reservationIDExists(int reservationID) const;
    bool studentIDIsValid(int studentID) const;
    bool resourceIDIsValid(int resourceID) const;

    void displayCancellationHistory() const;
};

#endif
