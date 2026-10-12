# CSCE-2110-project

Campus Resource Reservation System — Final Project

A console application written in C++ for reserving campus resources such as study rooms. The program loads a list of resources from a text file and then runs an interactive menu. From the menu a user can create and cancel reservations, undo the most recent cancellation, search for reservations and resources, manage a waiting list of students, and generate four system reports.

Team: Bobby Oliver, Shwet Naik, Bryce Harbison.

## Building and Running

Every source and header file lives in one flat directory. The program has no dependencies beyond the C++17 standard library. From that directory, compile and run with:

```
g++ -std=c++17 -Wall -Wextra *.cpp -o program
./program
```

Two details matter on Linux, which is what the UNT CSE CELL machines run. First, filenames are case sensitive, and the header that holds the cancellation stack must be named exactly `CancellationHistory.h` (capital C) because `ReservationManager.h` and `CancellationHistory.cpp` include it by that name. If the file is saved as `cancellationHistory.h`, the build fails with "No such file or directory" on Linux even though it works on Windows and macOS. Second, `resources.txt` is opened by relative path, so the program has to be started from the directory that contains it. If the file is missing the program prints "Error opening resources file." and exits.

## Resource File Format

`resources.txt` has one resource per line, with four fields separated by pipe characters:

```
ID|Name|Type|Availability
```

The availability field is `1` for available and anything else for unavailable. Blank lines are skipped. A sample line looks like this:

```
R101|Study Room 101|Study Room|1
```

## Source Files

| File | Contents |
|---|---|
| `main.cpp` | Loads `resources.txt`, prints the menus, and dispatches each menu choice |
| `Resource.h` / `Resource.cpp` | One reservable resource: ID, name, type, availability |
| `Reservation.h` / `Reservation.cpp` | One reservation record: reservation ID, student ID, student name, resource ID, date |
| `LinkedList.h` / `LinkedList.cpp` | Singly linked list that stores the active reservations |
| `WaitingList.h` / `WaitingList.cpp` | Linked-list queue of student IDs with front and rear pointers |
| `CancellationHistory.h` / `CancellationHistory.cpp` | Stack of cancelled reservations, built on `std::vector` |
| `ReservationManager.h` / `ReservationManager.cpp` | Owns the reservation list and the cancellation stack, validates requests, and implements create, cancel, and undo |
| `Search.h` / `Search.cpp` | Hand-written binary search on resource IDs, plus the merge sort and sortedness check that keep it correct |
| `Sorting.h` / `Sorting.cpp` | Hand-written merge sort used to rank resources in the Most Requested report |
| `SystemReports.h` / `SystemReports.cpp` | The four report functions |
| `resources.txt` | Sample data: four study rooms, R101 through R104 |
| `Complexity Report.txt` | Big-O discussion of the reservation list, waiting list, and undo |

`USER_GUIDE.md` explains how to operate the program and records the test results.

## Design Overview

The program is organized around a few small classes with one job each, and `main.cpp` stays thin by handing nearly all of the real work to them.

`ReservationManager` is the central class. It owns a `LinkedList` of active reservations and a `CancellationHistory` stack, and it is the only place that decides whether a reservation request is acceptable. `main.cpp` builds a `Reservation` from what the user typed and passes it to `createReservation`, which rejects it if the reservation ID is not positive or is already in use, if the student ID or resource ID is not positive, or if the student name or date is empty. Each rejection prints its own message. `WaitingList` and the `resources` vector are kept in `main` and passed by reference to the report functions, so the reports read the live data and do not keep copies of their own.

Active reservations are stored in a singly linked list that tracks only its head. Insertion walks to the tail, and removal walks until it finds the matching ID. The waiting list is a queue implemented as a linked list with both a front and a rear pointer, so adding a student and removing the next one are constant-time operations. Cancelled reservations go onto a stack, so undo always restores the most recent cancellation first.

Cancelling a reservation copies it, pushes the copy onto the stack, and then deletes the list node. The copy has to happen before the delete because `findReservation` returns a pointer into the node. Undo pops the stack and re-inserts the reservation at the tail of the list. If the popped reservation's ID has been reused by a newer reservation in the meantime, the undo is refused and the reservation is pushed back so the user can try again after fixing the conflict.

## Searching

The program offers three searches. Searching by reservation ID and searching by student ID are linear scans of the linked list, which is the only way to search a singly linked list. Searching by student ID returns the first matching reservation, not every reservation that student holds.

Searching for a resource by ID uses a binary search that the team wrote by hand in `Search.cpp`; it does not call `std::binary_search`, `std::find`, or `std::lower_bound`. Binary search is only correct on sorted data, so the entry point `Search::searchResourceByID` first calls `isSortedByResourceID`, which does one pass comparing neighbors. If the vector is not already in ascending order, it is sorted with the team's own merge sort before the search runs. Once sorted, the vector stays sorted, so later searches pay only for the O(n) check plus the O(log n) search. The sort and the search both compare IDs through the same function, `resourceIDLess`, so they always agree on what "sorted" means. The comparison is a plain string comparison, which means IDs are case sensitive: `R103` is found and `r103` is not.

## Sorting

Merge sort is implemented twice, once for each of the two things that needed sorting. `Search.cpp` has a merge sort over `Resource` objects ordered by resource ID, which supports the binary search. `Sorting.cpp` has a merge sort over `(count, label)` pairs, which the Most Requested Resources report uses to rank resources from most to fewest active reservations, breaking ties alphabetically by label. Both are top-down merge sorts that split a range in half, sort each half recursively, and merge the halves through a temporary buffer. No `std::sort` is used anywhere.

## Reports

The reports menu, option 13 on the main menu, provides four reports. Active Reservations lists every active reservation and prints a total. Resource Utilization lists each resource with the number of active reservations that refer to it. Most Requested Resources shows the same counts ranked by the merge sort. Waiting-List Statistics prints the total number of students currently waiting; see the limitations below for why it cannot break that number down by resource.

The reports match a resource to its reservations by turning a resource ID such as `R101` into the number 101, which is the form that reservations store. This is a workaround for the ID mismatch described in the limitations.

## Complexity Analysis

Let N be the number of active reservations, R the number of resources, and W the number of students on the waiting list. The reservation list is slower than it could be because it does not keep a pointer to its last node.



 Create reservation | O(N) | Checking for a duplicate ID scans the list, and inserting walks to the tail |
Cancel reservation | O(N) | Finding the ID scans the list; the stack push is O(1) |
Undo cancellation | O(N) | The stack pop is O(1), but the duplicate check and the re-insert each walk the list |
Search reservation by ID or by student | O(N) | Linear scan of a linked list |
Add student to waiting list / remove next | O(1) | Front and rear pointers mean no traversal |
Waiting-list count | O(W) | The queue does not store a counter, so it counts nodes | Merge sort of n items | O(n log n) time, O(n) extra space | Halving gives log n levels and each level merges n items; the merge uses a temporary buffer |
Binary search on resources | O(log R) | Each comparison halves the remaining range |
Resource search as called from the menu | O(R) once sorted, O(R log R) the first time | The sortedness check is one pass, and the sort only runs when the data is out of order | Active Reservations report | O(N) | Copies the list to a vector and prints it |
Resource Utilization report | O(R x N) | For each resource, scans every reservation |
Most Requested report | O(R x N + R log R) | Same counting step, then a merge sort of R entries |

