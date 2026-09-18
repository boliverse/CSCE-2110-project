#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "Reservation.h"
#include "CancellationHistory.h"

#include <vector>

class ReservationManager
{
private:

  
    std::vector<Reservation> reservations;

    
    CancellationHistory cancellationHistory;

public:

    
    // Reservation Management
    

    // Creates and validates a new reservation
    bool createReservation(const Reservation& reservation);

    // Cancels a reservation using its reservation ID
    bool cancelReservation(int reservationID);

    // Restores the most recently canceled reservation
    bool undoCancellation();

    // Displays all currently active reservations
    void displayReservations() const;

    
    // Searching
    

    // Searches for a reservation using Reservation ID
    Reservation* searchReservationByID(int reservationID);

    // Searches for a reservation using Student ID
    Reservation* searchReservationByStudentID(int studentID);

    
    // Validation
  

    // Checks whether a reservation ID already exists
    bool reservationIDExists(int reservationID) const;

    // Checks whether the student ID is valid
    bool studentIDIsValid(int studentID) const;

    // Checks whether the resource ID is valid
    bool resourceIDIsValid(int resourceID) const;

  
    // Cancellation History
    

    // Displays the cancellation history stack
    void displayCancellationHistory() const;
};

#endif
