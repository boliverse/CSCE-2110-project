#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Resource.h"

using namespace std;

int main()
{
    vector<Resource> resources;

    ifstream file("resources.txt");

    if (!file)
    {
        cout << "Error opening resources file." << endl;
        return 1;
    }

    string line;

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

    cout << "Campus Resources" << endl;

    for (Resource resource : resources)
    {
        resource.display();
    }

    return 0;
}