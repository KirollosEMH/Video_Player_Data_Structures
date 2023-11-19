#include "CircularLinkedList.hpp"

CircularLinkedList::CircularLinkedList()
{
}

CircularLinkedList::CircularLinkedList(const CircularLinkedList& origList): first(nullptr), mySize(origList.mySize)
{
}

CircularLinkedList::~CircularLinkedList()
{   
}

const CircularLinkedList& CircularLinkedList::operator=(const CircularLinkedList& rightSide)
{   
    mySize = rightSide.mySize;
    if (mySize == 0) {
        first = 0;
        return *this;
    }
    
    if (this != &rightSide)
    {
        this -> ~CircularLinkedList();
        NodePointer origPtr, lastPtr;
        first = new Node(rightSide.first->data);
        lastPtr = first;
        origPtr = rightSide.first->next;
        while (lastPtr != 0)
        {
            lastPtr->next = new Node(origPtr->data);
            origPtr = origPtr->next;
            lastPtr -> next -> prev = lastPtr;
            lastPtr = lastPtr->next;
        }
        lastPtr -> next = first;
        first -> prev = lastPtr; 
    }
    return *this;
    
    
}

bool CircularLinkedList::empty()
{
    
}


void CircularLinkedList::insert(ElementType dataVal, int index)
{
}

void CircularLinkedList::erase(int index)
{
    
}

int CircularLinkedList::search(ElementType dataVal)
{
    if (empty())
    {
        cerr << "The list is empty, returning -1" << endl;
        return -1;
    }
    
    int index = 0;
    NodePointer ptr = first;
    while (ptr ->data != dataVal && ptr != nullptr)
    {
        ptr = ptr -> next;
        index++;
    }
    if (ptr == nullptr)
    {
        cerr << "The value is not found" << endl;
        index = -1;
    }
    return index;
}

void CircularLinkedList::display(ostream& out) const
{
    
}

ostream& operator<<(ostream& out, const CircularLinkedList& aList)
{
    

}