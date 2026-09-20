#ifndef WAITINGLIST_H
#define WAITINGLIST_H

class WaitingList
{
private:
    struct Node
    {
        int studentID;
        Node* next;

        Node(int id) : studentID(id), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    WaitingList();
    ~WaitingList();

    // NOTE: "queue" is a weird name for the add function since queue is also
    // the name of the data structure (and of std::queue). enqueue/dequeue reads
    // better, but I left the original name so nothing else has to change.
    void queue(int studentID);
    void dequeue();
    void display() const;

    // added so main can tell whether the line is empty before printing
    bool isEmpty() const;
};

#endif
