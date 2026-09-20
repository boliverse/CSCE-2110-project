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

    // MISTAKE: these getters were not const, so they could not be called on a
    // const Resource (or on a const reference in a range-for loop). Added const.
    string getResourceID() const;
    string getResourceName() const;
    string getResourceType() const;
    bool isAvailable() const;

    // MISTAKE: setAvailable was declared here but never defined in Resource.cpp.
    // That is a linker error the moment anything calls it. Definition added.
    void setAvailable(bool status);

    void display() const;
};

#endif
