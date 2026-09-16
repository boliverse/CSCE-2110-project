#include "Reservation.h"
#include <iostream>
#include <iomanip>

Reservation::Reservation()
  : reservationId(""), studentID(""), studentName(""), resourceID(""), reservationDate("") {}

Reservation::Reservation(const std::string& reservationIDIn, const std::string& studentIDin, const std::string& studentNameIn, const std::string& resourceIdIn, const std::string& dateIn)
  : reservationID(reservationIDIN), studentID(studentIDIn), studentNName(studentNameIN), resourceID(resourceIDIn), reservationDate(dateIn) {}

std::string Reservation::getReservationID() const { return reservationID; }
std::string Reservation::getStudentID() const {return studentID; }
std::string Reservation::getStudentName() const { return studentName; }
std::string Reservation::getResourceID() const { return resourceID; }
std::string Reservation::getReservationDate() const { return reservationDate; }

void Reservation::display() const{
  std::cout << std::left
            << std::setw(10) << reservationID
            << std::setw(10) << studentID
            << std::setw(18) << stdentName
            << std::setw(10) << resourceID
            << reservationDate
            << std::endl;
}
