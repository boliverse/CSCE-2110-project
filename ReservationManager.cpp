#include "../include/ReservationManager.h"
#include <iostream>

using namespace std;

bool ReservationManager::reservationIDExists(int reservationID) const
{
    for (const Reservation& reservation : reservations)
    {
        if (reservation.getReservationID() == reservationID)
        {
            return true;
        }
    }

    return false;
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

    reservations.push_back(reservation);

    cout << "Reservation created successfully." << endl;

    return true;
}

bool ReservationManager::cancelReservation(int reservationID)
{
    for (auto it = reservations.begin();
         it != reservations.end();
         ++it)
    {
        if (it->getReservationID() == reservationID)
        {
            Reservation cancelledReservation = *it;

            cancellationHistory.push(cancelledReservation);

            reservations.erase(it);

            cout << "Reservation cancelled successfully." << endl;

            return true;
        }
    }

    cout << "Reservation not found." << endl;

    return false;
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
        cout << "Cannot restore reservation because its ID "
             << "already exists." << endl;

        return false;
    }

    reservations.push_back(restoredReservation);

    cout << "Most recent cancellation has been undone." << endl;

    return true;
}

void ReservationManager::displayReservations() const
{
    if (reservations.empty())
    {
        cout << "There are no active reservations." << endl;
        return;
    }

    cout << "\n===== Active Reservations =====\n";

    for (const Reservation& reservation : reservations)
    {
        reservation.display();
    }
}

Reservation* ReservationManager::searchReservationByID(
    int reservationID)
{
    for (Reservation& reservation : reservations)
    {
        if (reservation.getReservationID() == reservationID)
        {
            return &reservation;
        }
    }

    return nullptr;
}

Reservation* ReservationManager::searchReservationByStudentID(
    int studentID)
{
    for (Reservation& reservation : reservations)
    {
        if (reservation.getStudentID() == studentID)
        {
            return &reservation;
        }
    }

    return nullptr;
}

void ReservationManager::displayCancellationHistory() const
{
    cancellationHistory.display();
}
