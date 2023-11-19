//
// Created by Kiro on 11/19/2023.
//

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
        Node() : next(0) {}
        Node(ElementType dataValue) : data(dataValue), next(0) {}
    };

    typedef Node* NodePointer;
    NodePointer first;
    int mySize;

public:
    CircularLinkedList();
    CircularLinkedList(const CircularLinkedList& origList);
    ~CircularLinkedList();
    const CircularLinkedList& operator=(const CircularLinkedList& rightSide);
    bool empty();
    void insert(ElementType dataVal, int index);
    void erase(int index);
    int search(ElementType dataVal);
    void display(ostream& out) const;
};

ostream& operator<<(ostream& out, const CircularLinkedList& aList);

#endif //VIDEO_PLAYER_DATA_STRUCTURES_CIRCULAR_LINKED_LIST_H
