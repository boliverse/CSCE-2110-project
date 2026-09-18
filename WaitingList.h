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

    void queue(int studentID);
    void dequeue();
    void display() const;
};

#endif
