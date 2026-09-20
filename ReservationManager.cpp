// MISTAKE: same bad path as CancellationHistory.cpp. "../include/..." does not
// exist, the headers are in the same folder as the .cpp files.
#include "ReservationManager.h"
#include <iostream>

using namespace std;

bool ReservationManager::reservationIDExists(int reservationID) const
{
    return reservations.findReservation(reservationID) != nullptr;
}

bool ReservationManager::studentIDIsValid(int studentID) const
{
    return studentID > 0;
}

bool ReservationManager::resourceIDIsValid(int resourceID) const
{
    return resourceID > 0;
}

bool ReservationManager::createReservation(
    const Reservation& reservation)
{
    if (reservation.getReservationID() <= 0)
    {
        cout << "Invalid reservation ID." << endl;
        return false;
    }

    if (reservationIDExists(reservation.getReservationID()))
    {
        cout << "Reservation ID already exists." << endl;
        return false;
    }

    if (!studentIDIsValid(reservation.getStudentID()))
    {
        cout << "Invalid student ID." << endl;
        return false;
    }

    if (!resourceIDIsValid(reservation.getResourceID()))
    {
        cout << "Invalid resource ID." << endl;
        return false;
    }

    if (reservation.getStudentName().empty())
    {
        cout << "Student name cannot be empty." << endl;
        return false;
    }

    if (reservation.getReservationDate().empty())
    {
        cout << "Reservation date cannot be empty." << endl;
        return false;
    }

    reservations.insertReservation(reservation);

    cout << "Reservation created successfully." << endl;

    return true;
}

bool ReservationManager::cancelReservation(int reservationID)
{
    Reservation* reservation =
        reservations.findReservation(reservationID);

    if (reservation == nullptr)
    {
        cout << "Reservation not found." << endl;
        return false;
    }

    // NOTE: this copy matters. removeReservation deletes the node, so the
    // pointer above would be dangling right after. Copying first is correct,
    // just leaving a note so it does not get "cleaned up" later by accident.
    Reservation cancelledReservation = *reservation;

    cancellationHistory.push(cancelledReservation);

    reservations.removeReservation(reservationID);

    cout << "Reservation cancelled successfully." << endl;

    return true;
}

bool ReservationManager::undoCancellation()
{
    Reservation restoredReservation;

    if (!cancellationHistory.pop(restoredReservation))
    {
        cout << "There are no cancellations to undo." << endl;
        return false;
    }

    if (reservationIDExists(
            restoredReservation.getReservationID()))
    {
        // MISTAKE (behavior): the old code already popped the cancellation off
        // the stack, then bailed out here without putting it back. The
        // cancellation was silently lost forever. Pushing it back so the undo
        // can be retried later.
        cancellationHistory.push(restoredReservation);

        cout << "Cannot restore reservation because its ID "
             << "already exists." << endl;

        return false;
    }

    reservations.insertReservation(restoredReservation);

    cout << "Most recent cancellation has been undone." << endl;

    return true;
}

void ReservationManager::displayReservations() const
{
    cout << "\n===== Active Reservations =====" << endl;

    // this called a function that did not exist yet, see LinkedList.h
    reservations.displayReservations();
}

Reservation* ReservationManager::searchReservationByID(
    int reservationID)
{
    return reservations.findReservation(reservationID);
}

Reservation* ReservationManager::searchReservationByStudentID(
    int studentID)
{
    // MISTAKE: this function used to be "return nullptr;" no matter what, so
    // searching by student ID always said not found. Now it actually searches.
    return reservations.findReservationByStudentID(studentID);
}

void ReservationManager::displayCancellationHistory() const
{
    cancellationHistory.display();
}
