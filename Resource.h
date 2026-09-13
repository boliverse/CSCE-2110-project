#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

using namespace std;

class Resource
{

private:
    string resourceID;
    string resourceName;
    string resourceType;
    bool available;

public:
    Resource();
    Resource(string id, string name, string type, bool status);

    string getResourceID();
    string getResourceName();
    string getResourceType();
    bool isAvailable();

    void setAvailable(bool status);

    void display();

};










#endif