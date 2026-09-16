#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

class Reservation
{
private:
    int reservationID;
    int studentID;
    std::string studentName;
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
