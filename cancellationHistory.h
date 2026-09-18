#ifndef CANCELLATION_HISTORY_H
#define CANCELLATION_HISTORY_H

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
