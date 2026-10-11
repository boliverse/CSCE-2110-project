#ifndef SYSTEM_REPORTS_H
#define SYSTEM_REPORTS_H

#include <vector>
#include "Resource.h"
#include "ReservationManager.h"
#include "WaitingList.h"

class SystemReports
{

public:
    static void activeReservations(const ReservationManager& manager);
    static void resourceUtilization(const std::vector<Resource>& resources, const ReservationManager& manager);
    static void mostRequestedResources(const std::vector<Resource>& resources, const ReservationManager& manager);
    static void waitingListStatistics(const std::vector<Resource>& resources, const WaitingList& waitingList);
};

#endif
