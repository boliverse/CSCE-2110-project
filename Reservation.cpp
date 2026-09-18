#include "../include/Reservation.h"
#include <iostream>

using namespace std;

Reservation::Reservation()
{
    reservationID = 0;
    studentID = 0;
    studentName = "";
    resourceID = 0;
    reservationDate = "";
}

Reservation::Reservation(int reservationID,
                         int studentID,
                         const string& studentName,
                         int resourceID,
                         const string& reservationDate)
{
    this->reservationID = reservationID;
    this->studentID = studentID;
    this->studentName = studentName;
    this->resourceID = resourceID;
    this->reservationDate = reservationDate;
}

int Reservation::getReservationID() const
{
    return reservationID;
}

int Reservation::getStudentID() const
{
    return studentID;
}

string Reservation::getStudentName() const
{
    return studentName;
}

int Reservation::getResourceID() const
{
    return resourceID;
}

string Reservation::getReservationDate() const
{
    return reservationDate;
}

void Reservation::setReservationID(int id)
{
    reservationID = id;
}

void Reservation::setStudentID(int id)
{
    studentID = id;
}

void Reservation::setStudentName(const string& name)
{
    studentName = name;
}

void Reservation::setResourceID(int id)
{
    resourceID = id;
}

void Reservation::setReservationDate(const string& date)
{
    reservationDate = date;
}

void Reservation::display() const
{
    cout << "Reservation ID: " << reservationID << endl;
    cout << "Student ID: " << studentID << endl;
    cout << "Student Name: " << studentName << endl;
    cout << "Resource ID: " << resourceID << endl;
    cout << "Reservation Date: " << reservationDate << endl;
    cout << "-----------------------------" << endl;
}
