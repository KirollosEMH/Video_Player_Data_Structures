#include "CircularLinkedList.hpp"

CircularLinkedList::CircularLinkedList()
{
}

CircularLinkedList::CircularLinkedList(const CircularLinkedList& origList): first(nullptr), mySize(origList.mySize)
{
    NodePointer origCurrent = origList.first;
    NodePointer newCurrent = new Node(origCurrent->data);
    first = newCurrent;

    origCurrent = origCurrent->next;
    while (origCurrent != origList.first) {
        NodePointer newNode = new Node(origCurrent->data);
        newCurrent->next = newNode;
        newNode->prev = newCurrent;
        newCurrent = newNode;
        origCurrent = origCurrent->next;
    }

    newCurrent->next = first;
    first->prev = newCurrent;
}

CircularLinkedList::~CircularLinkedList()
{   
}

const CircularLinkedList& CircularLinkedList::operator=(const CircularLinkedList& rightSide)
{  
    
}

bool CircularLinkedList::empty()
{
    
}

void CircularLinkedList::insert(ElementType dataVal, int index)
{
    if (index < 0 || index > mySize) {
        cout << "Invalid index\n";
    }

    NodePointer newNode = new Node(dataVal);

    if (empty()) {
        first = newNode;
        first->next = first;
        first->prev = first;
    } else if (index == 0) {
        newNode->next = first;
        newNode->prev = first->prev;
        first->prev->next = newNode;
        first->prev = newNode;
        first = newNode;
    } else if (index == mySize) {
        newNode->next = first;
        newNode->prev = first->prev;
        first->prev->next = newNode;
        first->prev = newNode;
    } else {
        NodePointer current = first;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
    }

    mySize++;
}
    


void CircularLinkedList::erase(int index)
{
    
}

int CircularLinkedList::search(ElementType dataVal)
{
    
}

void CircularLinkedList::display(ostream& out) const
{
    
}

ostream& operator<<(ostream& out, const CircularLinkedList& aList)
{
    
}