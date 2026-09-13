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

string Resource::getResourceID()
{
    return resourceID;
}

string Resource::getResourceName()
{
    return resourceName;
}

string Resource::getResourceType()
{
    return resourceType;
}

bool Resource::isAvailable()
{
    return available;
}

void Resource::display()
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