#include "SystemReports.h"
#include "Sorting.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

static int numericResourceID(const string& id)
{
    try
    {
        if(!id.empty() && id[0] == 'R')
        {
            return stoi(id.substr(1));
        }

        return stoi(id);
    }
    catch (...)
    {
        return -1;
    }
}

void SystemReports::activeReservations(const ReservationManager& manager)
{
    cout << "\n===== Active Reservations Report =====\n";

    vector<Reservation> reservations = manager.getAllReservations();

    if(reservations.empty())
    {
        cout << "There are no active reservations." << endl;
        return;
    }

    for(const Reservation& reservation : reservations)
    {
        reservation.display();
    }

    cout << "Total active reservations: " << reservations.size() << endl;
}

void SystemReports::resourceUtilization(const vector<Resource>& resources, const ReservationManager& manager)
{
    cout << "\n===== Resource Utilization Report =====\n";

    vector<Reservation> reservations = manager.getAllReservations();

    for(const Resource& resource : resources)
    {
        int count = 0;
        int resourceID = numericResourceID(resource.getResourceID());
      
        for(const Reservation& reservation : reservations)
        {
            if(reservation.getResourceID() == resourceID)
            {
                ++count;
            }
        }

        cout << "Resource ID: " << resource.getResourceID() << endl;
        cout << "Resource Name: " << resource.getResourceName() << endl;
        cout << "Active reservations: " << count << endl;
        cout << "-----------------------------\n";
    }
}

void SystemReports::mostRequestedResources(const vector<Resource>& resources, const ReservationManager& manager)
{
    cout << "\n===== Most Requested Resources =====\n";
    cout << "(Ranked by current active reservations)\n";

    vector<Reservation> reservations = manager.getAllReservations();

    vector<pair<int, string>> counts;

    for(const Resource& resource : resources)
    {
        int count = 0;
        int resourceID = numericResourceID(resource.getResourceID());

        for(const Reservation& reservation : reservations)
        {
            if(reservation.getResourceID() == resourceID)
            {
                ++count;
            }
        }

        counts.push_back(make_pair(count, resource.getResourceID() + " - " + resource.getResourceName()));
    }
    
    Sorting::sortResourceCounts(counts);
  
    int rank = 1;

    for(const auto& item : counts)
    {
        cout << rank++ << ". " << item.second << " | Active reservations: " << item.first << endl;
    }

    if(counts.empty())
    {
        cout << "No resources found.\n";
    }
}


void SystemReports::waitingListStatistics(const vector<Resource>& resources, const WaitingList& waitingList)
{
    cout << "\n===== Waiting-List Statistics =====\n";
    cout << "Total students currently waiting: " << waitingList.getWaitingCount() << endl;
    cout << "\nWaiting-list counts by resource:\n";

    for(const Resource& resource : resources)
    {
        cout << resource.getResourceID() << " - " << resource.getResourceName() << ": Not tracked separately\n";
    }

    cout << "\nThe current waiting list stores student IDs " << "without resource IDs, so per-resource counts " << "cannot be calculated accurately.\n";
}
