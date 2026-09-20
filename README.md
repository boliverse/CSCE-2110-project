# CSCE-2110-project

Campus Resource Reservation System — Milestone 1

A console application for reserving campus resources such as study rooms. The
program loads a list of resources from a file, then lets the user create and
cancel reservations, search for them, manage a waiting list of students, and
undo the most recent cancellation.

## Building and Running

All source and header files are in a single directory. Compile with:

```
g++ -std=c++17 -Wall -Wextra *.cpp -o program
./program
```

`resources.txt` must be in the same directory the program is run from, since
the file is opened by relative path.

## Resource File Format

`resources.txt` is pipe-delimited, one resource per line:

```
ID|Name|Type|Availability
```

Availability is `1` for available and anything else for unavailable. For
example:

```
R101|Study Room 101|Study Room|1
```

## Files

| File | Contents |
|---|---|
| `main.cpp` | File loading and the interactive menu loop |
| `Resource.h` / `Resource.cpp` | A single reservable resource and its availability |
| `Reservation.h` / `Reservation.cpp` | A single reservation record |
| `LinkedList.h` / `LinkedList.cpp` | Singly linked list storing active reservations |
| `WaitingList.h` / `WaitingList.cpp` | Queue of student IDs waiting for a resource |
| `CancellationHistory.h` / `CancellationHistory.cpp` | Stack of cancelled reservations |
| `ReservationManager.h` / `ReservationManager.cpp` | Coordinates the above and validates requests |
| `resources.txt` | Sample resource data |
| `ComplexityAnalysis.md` | Big-O discussion of the core operations |

## Data Structures

Active reservations are stored in a singly linked list, which supports
insertion at the tail, removal by reservation ID, traversal, and display of a
single record or all records.

The waiting list is a queue implemented as a linked list with both front and
rear pointers, so adding and removing students are constant-time operations.

Cancellation history is a stack. Cancelled reservations are pushed on
cancellation and popped in last-in-first-out order when an undo is requested,
which restores the most recent cancellation first.

## Menu Options

The program runs a menu loop offering: display resources, create a reservation,
cancel a reservation, undo the last cancellation, display active reservations,
search by reservation ID, search by student ID, display cancellation history,
add a student to the waiting list, remove the next student from the waiting
list, display the waiting list, and quit.

## Validation

`ReservationManager::createReservation` rejects a request when the reservation
ID is not positive, when the reservation ID is already in use, when the student
ID or resource ID is not positive, or when the student name or reservation date
is empty. An undo is rejected if the reservation ID it would restore is already
in use again, and in that case the cancellation is pushed back onto the history
so it can be retried.

## Known Limitations

`Resource` stores its ID as a string such as `R101`, while `Reservation` stores
its resource ID as an integer, so reservations are not yet linked to specific
resources in the loaded resource list. Creating a reservation also does not
update a resource's availability flag, and the waiting list is global rather
than per-resource.
