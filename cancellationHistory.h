#ifndef CANCELLATION_HISTORY_H
#define CANCELLATION_HISTORY_H

// MISTAKE: this file used to be named "cancellationHistory.h" (lowercase c) but
// ReservationManager.h includes "CancellationHistory.h". On Windows that works
// by luck because filenames are not case sensitive, on Linux/Mac (and on most
// graders) it fails. Renamed the file so the capitalization matches.

#include "Reservation.h"
#include <vector>

class CancellationHistory
{
private:
    std::vector<Reservation> history;

public:
    void push(const Reservation& reservation);

    bool pop(Reservation& reservation);

    bool isEmpty() const;

    void display() const;

    int size() const;
};

#endif
