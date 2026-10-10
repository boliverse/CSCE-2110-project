#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>
#include "Resource.h"

// Search.h / Search.cpp
//
// Hand-written Binary Search for finding a Resource by its ID (e.g. "R101").
// No std::find, std::binary_search, std::lower_bound or std::sort is used.
//
// Binary search only works on SORTED data, so this file also contains its own
// merge sort and a sortedness check. searchResourceByID() makes sure the data
// is sorted before it searches.

namespace Search
{
    // Compares two resource IDs. The sort and the search both use this, so they
    // always agree on what "sorted" means (plain string comparison).
    bool resourceIDLess(const std::string& a, const std::string& b);

    // true if the vector is already in ascending order by resource ID. O(n)
    bool isSortedByResourceID(const std::vector<Resource>& resources);

    // Merge sort, ascending by resource ID. O(n log n)
    void sortResourcesByID(std::vector<Resource>& resources);

    // Binary search. PRECONDITION: resources is sorted by ID.
    // Returns the index of the match, or -1 if not found. O(log n)
    int binarySearchResourceByID(const std::vector<Resource>& resources,
                                 const std::string& resourceID);

    // Safe wrapper used by the system: sorts the vector first if (and only if)
    // it is not already sorted, then runs the binary search. The returned index
    // refers to the vector AFTER sorting. Returns -1 if not found.
    int searchResourceByID(std::vector<Resource>& resources,
                           const std::string& resourceID);
}

#endif
