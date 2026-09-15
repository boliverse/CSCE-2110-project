#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Resource.h"

using namespace std;

int main()
{
    // this vector stores the info about the reservable items and locations
    vector<Resource> resources;
    // imports the file into program to be read
    ifstream file("resources.txt");

    // just checks if the file is infact a file
    if (!file)
    {
        cout << "Error opening resources file." << endl;
        return 1;
    }

    string line;
    // this reads the file line by line assigning each string the approiate info between the |'s
    // also expands the vector as more info is assigned
    while (getline(file, line))
    {
        string id;
        string name;
        string type;
        string status;

        stringstream ss(line);

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, status, '|');

        bool available = (status == "1");

        Resource resource(id, name, type, available);

        resources.push_back(resource);
    }
    
    file.close();
// this is all output using the display function located in resource.cpp
    cout << "Campus Resources" << endl;

    for (Resource resource : resources)
    {
        resource.display();
    }

    return 0;
}