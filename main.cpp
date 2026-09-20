#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Resource.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include "WaitingList.h"

using namespace std;

// reads resources.txt into the vector, returns false if the file is missing
bool loadResources(vector<Resource>& resources)
{
    ifstream file("resources.txt");

    if (!file)
    {
        cout << "Error opening resources file." << endl;
        return false;
    }

    string line;

    // this reads the file line by line assigning each string the info
    // between the |'s, and grows the vector as it goes
    while (getline(file, line))
    {
        // MISTAKE: the old loop did not skip blank lines. An empty line (or the
        // blank line a lot of editors leave at the end of a file) turned into a
        // Resource with empty fields that still got printed.
        if (line.empty())
        {
            continue;
        }

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

    return true;
}

void displayResources(const vector<Resource>& resources)
{
    cout << "Campus Resources" << endl;

    // MISTAKE: the old loop was "for (Resource resource : resources)" which
    // copies every Resource object on every pass. const reference instead.
    for (const Resource& resource : resources)
    {
        resource.display();
    }
}

void printMenu()
{
    cout << "\n Campus Reservation System " << endl;
    cout << "1. Display resources" << endl;
    cout << "2. Create a reservation" << endl;
    cout << "3. Cancel a reservation" << endl;
    cout << "4. Undo last cancellation" << endl;
    cout << "5. Display active reservations" << endl;
    cout << "6. Search by reservation ID" << endl;
    cout << "7. Search by student ID" << endl;
    cout << "8. Display cancellation history" << endl;
    cout << "9. Add a student to the waiting list" << endl;
    cout << "10. Remove next student from the waiting list" << endl;
    cout << "11. Display waiting list" << endl;
    cout << "0. Quit" << endl;
    cout << "Choice: ";
}

int main()
{
    // this vector stores the info about the reservable items and locations
    vector<Resource> resources;

    if (!loadResources(resources))
    {
        return 1;
    }

    // MISTAKE (design): the old main only read the file and printed it. It never
    // created a ReservationManager or a WaitingList, so LinkedList,
    // CancellationHistory, ReservationManager and WaitingList were all dead code
    // that nothing ever called. Added a menu so the classes actually get used.
    ReservationManager manager;
    WaitingList waitingList;

    int choice = -1;

    while (choice != 0)
    {
        printMenu();

        // if the user types letters instead of a number, cin fails and the
        // loop would spin forever, so clear the error and throw the line away
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number." << endl;
            continue;
        }

        if (choice == 1)
        {
            displayResources(resources);
        }
        else if (choice == 2)
        {
            int reservationID;
            int studentID;
            string studentName;
            int resourceID;
            string date;

            cout << "Reservation ID: ";
            cin >> reservationID;

            cout << "Student ID: ";
            cin >> studentID;

            cin.ignore(10000, '\n');

            cout << "Student name: ";
            getline(cin, studentName);

            cout << "Resource ID (number): ";
            cin >> resourceID;

            cin.ignore(10000, '\n');

            cout << "Date (MM/DD/YYYY): ";
            getline(cin, date);

            Reservation reservation(reservationID,
                                    studentID,
                                    studentName,
                                    resourceID,
                                    date);

            manager.createReservation(reservation);
        }
        else if (choice == 3)
        {
            int reservationID;

            cout << "Reservation ID to cancel: ";
            cin >> reservationID;

            manager.cancelReservation(reservationID);
        }
        else if (choice == 4)
        {
            manager.undoCancellation();
        }
        else if (choice == 5)
        {
            manager.displayReservations();
        }
        else if (choice == 6)
        {
            int reservationID;

            cout << "Reservation ID to search: ";
            cin >> reservationID;

            Reservation* found =
                manager.searchReservationByID(reservationID);

            if (found == nullptr)
            {
                cout << "Reservation not found." << endl;
            }
            else
            {
                found->display();
            }
        }
        else if (choice == 7)
        {
            int studentID;

            cout << "Student ID to search: ";
            cin >> studentID;

            Reservation* found =
                manager.searchReservationByStudentID(studentID);

            if (found == nullptr)
            {
                cout << "No reservation found for that student." << endl;
            }
            else
            {
                found->display();
            }
        }
        else if (choice == 8)
        {
            manager.displayCancellationHistory();
        }
        else if (choice == 9)
        {
            int studentID;

            cout << "Student ID to add to the waiting list: ";
            cin >> studentID;

            waitingList.queue(studentID);

            cout << "Student added to the waiting list." << endl;
        }
        else if (choice == 10)
        {
            waitingList.dequeue();
        }
        else if (choice == 11)
        {
            cout << "\n===== Waiting List =====" << endl;
            waitingList.display();
        }
        else if (choice != 0)
        {
            cout << "That is not one of the options." << endl;
        }
    }

    cout << "Goodbye." << endl;

    return 0;
}
