#include "../include/CancellationHistory.h"
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

    for (int i = static_cast<int>(history.size()) - 1; i >= 0; i--)
    {
        cout << "\nCancellation #" 
             << history.size() - i << endl;

        history[i].display();
    }
}
