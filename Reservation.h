#ifndef RESERVATION.H
#define RESERVATION.H

#include <string>

struct Reservation {
int reservationID;
std::string studentID;
std::string resourceID;
std::string date;
std::string startTime;
std::string endTime;
std::string status;

Reservation()
: reservationID(-1), status("ACTIVE") {}

Reservation(int id, const std::string& sID, const std::string& rID,
         const std::string& d, const std::string& start, const std::string& end)
: reservation(id), studentID(sID), resourceID(rID),
  date(d), startTime(start), endTime(end), status("ACTIVE") {}
};

#endif 
