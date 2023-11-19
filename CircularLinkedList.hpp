#ifndef VIDEO_PLAYER_DATA_STRUCTURES_CIRCULAR_LINKED_LIST_H
#define VIDEO_PLAYER_DATA_STRUCTURES_CIRCULAR_LINKED_LIST_H

#include <iostream>
using namespace std;
typedef int ElementType;

class CircularLinkedList {
private:
    class Node {
    public:
        ElementType data;
        Node* next;
        Node* prev;
        Node() : next(0),prev(0) {}
        Node(ElementType dataValue) : data(dataValue), next(0),prev(0) {}
    };

    typedef Node* NodePointer;
    NodePointer first;
    int mySize;

public:
    CircularLinkedList(); // fadel 
    CircularLinkedList(const CircularLinkedList& origList); // kiro
    ~CircularLinkedList(); // fadel
    const CircularLinkedList& operator=(const CircularLinkedList& rightSide); // nezar
    bool empty(); // fadel
    void insert(ElementType dataVal, int pos); // kiro
    void erase(int index); // abdulrahman
    int search(ElementType dataVal); // Nezar 
    void display(ostream& out) const; // abdulrahman
};

ostream& operator<<(ostream& out, const CircularLinkedList& aList); // nezar

#endif //VIDEO_PLAYER_DATA_STRUCTURES_CIRCULAR_LINKED_LIST_H
