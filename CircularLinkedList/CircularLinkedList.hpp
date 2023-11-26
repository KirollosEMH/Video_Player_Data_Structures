#ifndef VIDEO_PLAYER_DATA_STRUCTURES_CIRCULAR_LINKED_LIST_H
#define VIDEO_PLAYER_DATA_STRUCTURES_CIRCULAR_LINKED_LIST_H

#include <iostream>
using namespace std;

template <typename ElementType>
class CircularLinkedList {
private:
    class Node {
    public:
        ElementType data;
        Node* next;
        Node* prev;
        Node() : next(nullptr), prev(nullptr) {}
        Node(ElementType dataValue) : data(dataValue), next(nullptr), prev(nullptr) {}
    };

    typedef Node* NodePointer;
    NodePointer first;
    NodePointer currentPtr;
    int mySize;

public:
    CircularLinkedList(); // fadel
    CircularLinkedList(const CircularLinkedList& origList); // kiro
    ~CircularLinkedList(); // fadel
    const CircularLinkedList& operator=(const CircularLinkedList& rightSide); // nezar
    bool empty() const; // fadel
    void insert(ElementType dataVal, int pos); // kiro
    void erase(int index); // abdulrahman
    int search(ElementType dataVal); // Nezar
    void display(ostream& out) const; // abdulrahman
    int getSize() const; // kiro
    void rotateNext(); // abdulrahman
    void rotatePrevious(); // abdulrahman
    ElementType getCurrentData() const; // abdulrahman
    void clear(); // abdulrahman

};

template <typename ElementType>
ostream& operator<<(ostream& out, const CircularLinkedList<ElementType>& aList); // nezar

#endif // VIDEO_PLAYER_DATA_STRUCTURES_CIRCULAR_LINKED_LIST
