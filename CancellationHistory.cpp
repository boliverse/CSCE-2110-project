// MISTAKE: this was #include "../include/CancellationHistory.h". There is no
// include folder in this project, everything sits in one directory, so the
// compiler stopped with "No such file or directory". Same problem was in
// ReservationManager.cpp.
#include "CancellationHistory.h"
#include <iostream>

using namespace std;

void CancellationHistory::push(const Reservation& reservation)
{
    history.push_back(reservation);
}

bool CancellationHistory::pop(Reservation& reservation)
{
    if (history.empty())
    {
        return false;
    }

    reservation = history.back();
    history.pop_back();

    return true;
}

bool CancellationHistory::isEmpty() const
{
    return history.empty();
}

int CancellationHistory::size() const
{
    return static_cast<int>(history.size());
}

void CancellationHistory::display() const
{
    if (history.empty())
    {
        cout << "Cancellation history is empty." << endl;
        return;
    }

    cout << "\n===== Cancellation History =====\n";

    int total = static_cast<int>(history.size());

    for (int i = total - 1; i >= 0; i--)
    {
        // MISTAKE: this used to be history.size() - i, which mixes an unsigned
        // size_t with an int. That gives a signed/unsigned warning and can
        // print a garbage huge number. Using two ints instead.
        cout << "\nCancellation #" << (total - i) << endl;

        history[i].display();
    }
}
