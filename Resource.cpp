#include "Resource.h"
#include <iostream>

using namespace std;

Resource::Resource()
{
    resourceID = "";
    resourceName = "";
    resourceType = "";
    available = true;
}

Resource::Resource(string id, string name, string type, bool status)
{
    resourceID = id;
    resourceName = name;
    resourceType = type;
    available = status;
}

string Resource::getResourceID() const
{
    return resourceID;
}

string Resource::getResourceName() const
{
    return resourceName;
}

string Resource::getResourceType() const
{
    return resourceType;
}

bool Resource::isAvailable() const
{
    return available;
}

// MISTAKE (fixed): this function was missing entirely even though the header
// promised it existed.
void Resource::setAvailable(bool status)
{
    available = status;
}

void Resource::display() const
{
    cout << resourceID << " | "
         << resourceName << " | "
         << resourceType << " | ";

    if (available)
        cout << "Available";
    else
        cout << "Unavailable";

    cout << endl;
}
