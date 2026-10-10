#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>
#include "Resource.h"
#include "Reservation.h"



namespace Search
{


    // Compares two resources by ID. Used by the sort and the binary search so


    bool resourceIDLess(const std::string& a, const std::string& b);

    // true if the vector is already in ascending order by resource ID. O(n)
    bool isSortedByResourceID(const std::vector<Resource>& resources);

    // Merge sort, ascending by resource ID. O(n log n)
    void sortResourcesByID(std::vector<Resource>& resources);

    // Binary search. 
    int binarySearchResourceByID(const std::vector<Resource>& resources,
                                 const std::string& resourceID);

   
   
    int searchResourceByID(std::vector<Resource>& resources,
                           const std::string& resourceID);

    // ---------------- Linear search on reservations ----------------

    // Index of the reservation with this reservation ID.
    int linearSearchReservationByID(const std::vector<Reservation>& reservations,
                                    int reservationID);

    // Indexes of EVERY reservation belonging to this student (empty if none),

    std::vector<int> linearSearchReservationsByStudentID(
        const std::vector<Reservation>& reservations,
        int studentID);
}

#endif