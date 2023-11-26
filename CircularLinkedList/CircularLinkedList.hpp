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
    CircularLinkedList();
    CircularLinkedList(const CircularLinkedList& origList);
    ~CircularLinkedList();
    const CircularLinkedList& operator=(const CircularLinkedList& rightSide);
    bool empty() const;
    void insert(ElementType dataVal, int pos);
    void erase(int index);
    int search(ElementType dataVal);
    void display(ostream& out) const;
    int getSize() const;
    void rotateNext();
    void rotatePrevious();
    ElementType getCurrentData() const;
    void clear();
    void organizeV1(ElementType dataVal, int pos);

};



template <typename ElementType>
ostream& operator<<(ostream& out, const CircularLinkedList<ElementType>& aList); // nezar

#endif // VIDEO_PLAYER_DATA_STRUCTURES_CIRCULAR_LINKED_LIST
