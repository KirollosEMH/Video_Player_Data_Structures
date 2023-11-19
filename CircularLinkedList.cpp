#include "CircularLinkedList.hpp"

CircularLinkedList::CircularLinkedList()
{
    first = NULL;
    mySize = 0;
    
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

CircularLinkedList::~CircularLinkedList() {
    NodePointer current = first;
    do {
        NodePointer next = current->next;
        delete current;
        current = next;
    } while (current != nullptr);
    
    first = nullptr;
    mySize = 0; 
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
        // this -> ~CircularLinkedList();
        NodePointer origPtr, lastPtr;
        first = new Node(rightSide.first->data);
        lastPtr = first;
        origPtr = rightSide.first->next;
       while (origPtr != rightSide.first)
        {
              NodePointer newNode = new Node(origPtr->data);
              lastPtr->next = newNode;
              lastPtr -> next -> prev = lastPtr;
              lastPtr = lastPtr->next;
              origPtr = origPtr->next;
        }
        lastPtr->next = first;
        first->prev = lastPtr; 
    }
    return *this;
    
}

bool CircularLinkedList::empty() const
{
    return first == nullptr;; 
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
    if (empty() || index < 0 || index >= mySize) {
        cerr << "Invalid index or list is empty" << endl;
        return;
    }

    NodePointer toDelete;
    if (index == 0) {
        toDelete = first;
        if (mySize == 1) {
            first = nullptr;
        } else {
            first->prev->next = first->next;
            first->next->prev = first->prev;
            first = first->next;
        }
    } else {
        NodePointer current = first;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        toDelete = current;
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    delete toDelete;
    mySize--;
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
    if (empty()) {
        out << "List is empty" << endl;
        return;
    }

    NodePointer current = first;
    do
    {
        out << current->data << " ";
        current = current->next;
    } while (current != first);
    
    
    out << endl;
}

ostream& operator<<(ostream& out, const CircularLinkedList& aList)
{
    aList.display(out);
    return out;
}