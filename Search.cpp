#include "Search.h"

using namespace std;

namespace Search
{
    // ---------------- Binary search on resources ----------------

    bool resourceIDLess(const string& a, const string& b)
    {
        return a < b;
    }

    bool isSortedByResourceID(const vector<Resource>& resources)
    {
        for (size_t i = 1; i < resources.size(); i++)
        {
            if (resourceIDLess(resources[i].getResourceID(),
                               resources[i - 1].getResourceID()))
            {
                return false;
            }
        }
        return true;
    }

    // merges the two sorted halves [left, mid) and [mid, right) of the vector
    static void mergeHalves(vector<Resource>& resources, vector<Resource>& temp,
                            size_t left, size_t mid, size_t right)
    {
        size_t i = left;
        size_t j = mid;
        size_t k = left;

        while (i < mid && j < right)
        {
            // take from the right half only if it is strictly smaller, so
            // equal IDs keep their original order (stable)
            if (resourceIDLess(resources[j].getResourceID(),
                               resources[i].getResourceID()))
            {
                temp[k++] = resources[j++];
            }
            else
            {
                temp[k++] = resources[i++];
            }
        }

        while (i < mid)
        {
            temp[k++] = resources[i++];
        }

        while (j < right)
        {
            temp[k++] = resources[j++];
        }

        for (size_t n = left; n < right; n++)
        {
            resources[n] = temp[n];
        }
    }

    static void mergeSortRange(vector<Resource>& resources, vector<Resource>& temp,
                               size_t left, size_t right)
    {
        if (right - left < 2)
        {
            return;
        }

        size_t mid = left + (right - left) / 2;

        mergeSortRange(resources, temp, left, mid);
        mergeSortRange(resources, temp, mid, right);
        mergeHalves(resources, temp, left, mid, right);
    }

    void sortResourcesByID(vector<Resource>& resources)
    {
        if (resources.size() < 2)
        {
            return;
        }

        vector<Resource> temp(resources.size());
        mergeSortRange(resources, temp, 0, resources.size());
    }

    int binarySearchResourceByID(const vector<Resource>& resources,
                                 const string& resourceID)
    {
        int low = 0;
        int high = static_cast<int>(resources.size()) - 1;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            const string midID = resources[mid].getResourceID();

            if (midID == resourceID)
            {
                return mid;
            }
            else if (resourceIDLess(midID, resourceID))
            {
                low = mid + 1;      // target is in the right half
            }
            else
            {
                high = mid - 1;     // target is in the left half
            }
        }

        return -1;
    }

    int searchResourceByID(vector<Resource>& resources, const string& resourceID)
    {
        // Binary search is only correct on sorted data, so check first and sort
        // only when needed. After the first call the data stays sorted, so
        // later searches skip the sort and cost O(n) check + O(log n) search.
        if (!isSortedByResourceID(resources))
        {
            sortResourcesByID(resources);
        }

        return binarySearchResourceByID(resources, resourceID);
    }
}
