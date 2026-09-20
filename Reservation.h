#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

class Reservation
{
private:
    int reservationID;
    int studentID;
    std::string studentName;

    // MISTAKE (design, NOT fixed on purpose): this is an int, but Resource
    // stores its ID as a string like "R101" from resources.txt. So a
    // reservation can never actually point at a real resource. I left the type
    // alone because changing it touches the whole class, but one of the two has
    // to change. Easiest fix is making this a std::string and dropping the
    // resourceIDIsValid(int) check in ReservationManager.
    int resourceID;
    std::string reservationDate;

public:
    Reservation();
    
    Reservation(int reservationID,
                int studentID,
                const std::string& studentName,
                int resourceID,
                const std::string& reservationDate);

    int getReservationID() const;
    int getStudentID() const;
    std::string getStudentName() const;
    int getResourceID() const;
    std::string getReservationDate() const;

    void setReservationID(int id);
    void setStudentID(int id);
    void setStudentName(const std::string& name);
    void setResourceID(int id);
    void setReservationDate(const std::string& date);

    void display() const;
};

#endif
