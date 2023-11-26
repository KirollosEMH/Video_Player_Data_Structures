#include "CircularLinkedList.hpp"
#include <opencv2/opencv.hpp>

template <typename ElementType>
CircularLinkedList<ElementType>::CircularLinkedList()
{
    first = nullptr;
    mySize = 0;
    currentPtr = nullptr;
}

template <typename ElementType>
CircularLinkedList<ElementType>::CircularLinkedList(const CircularLinkedList& origList): first(nullptr), mySize(origList.mySize), currentPtr(nullptr)
{
    NodePointer origCurrent = origList.first;
    NodePointer newCurrent = new Node(origCurrent->data);
    first = newCurrent;
    currentPtr = newCurrent;

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

template <typename ElementType>
CircularLinkedList<ElementType>::~CircularLinkedList() {
    if (first == nullptr) {
        return; 
    }
    NodePointer current = first;
    NodePointer last = first->prev; 

    while (current != last) {
        NodePointer next = current->next;
        delete current;
        current = next;
    }
    delete last;
    first = nullptr;
    mySize = 0;
}

template <typename ElementType>
const CircularLinkedList<ElementType>& CircularLinkedList<ElementType>::operator=(const CircularLinkedList& rightSide)
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
        currentPtr = first;
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

template <typename ElementType>
bool CircularLinkedList<ElementType>::empty() const
{
    return first == nullptr;; 
}

template <typename ElementType>
void CircularLinkedList<ElementType>::insert(ElementType dataVal, int index)
{
    if (index < 0 || index > mySize) {
        cout << "Invalid index\n";
    }

    NodePointer newNode = new Node(dataVal);

    if (empty()) {
        first = newNode;
        currentPtr = newNode;
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

template <typename ElementType>
void CircularLinkedList<ElementType>::erase(int index)
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

template <typename ElementType>
int CircularLinkedList<ElementType>::search(ElementType dataVal)
{
    if (empty())
    {
        cerr << "The list is empty, returning garbage: ";
        return -1;
    }

    int index = 0;
    NodePointer ptr = first;
    while (ptr ->data != dataVal && index < mySize)
    {
        ptr = ptr -> next;
        index++;
    }
    if (index == mySize)
    {
        cerr << "The value is not found garbage value returned: ";
        index = -1;
    }
    return index;
}

template <typename ElementType>
void CircularLinkedList<ElementType>::display(ostream& out) const
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

template <typename ElementType>
int CircularLinkedList<ElementType>::getSize() const
{
    return mySize;
}

template <typename ElementType>
void CircularLinkedList<ElementType>::rotateNext() {
    if (currentPtr != nullptr) {
        currentPtr = currentPtr->next;
    }
}

template <typename ElementType>
void CircularLinkedList<ElementType>::rotatePrevious() {
    if (currentPtr != nullptr) {
        currentPtr = currentPtr->prev;
    }
}

template <typename ElementType>
void CircularLinkedList<ElementType>::clear() {
    while (!empty()) {
        erase(0);
    }
    currentPtr = nullptr;
}

template <typename ElementType>
ElementType CircularLinkedList<ElementType>::getCurrentData() const {
    return (currentPtr != nullptr) ? currentPtr->data : ElementType();
}

template <typename ElementType>
ostream& operator<<(ostream& out, const CircularLinkedList<ElementType>& aList)
{
    aList.display(out);
    return out;
}

template class CircularLinkedList<int>;
template class CircularLinkedList<double>;
template class CircularLinkedList<string>;
//template class CircularLinkedList<cv::VideoCapture>;

template ostream& operator<<(ostream& out, const CircularLinkedList<int>& aList);
template ostream& operator<<(ostream& out, const CircularLinkedList<double>& aList);
template ostream& operator<<(ostream& out, const CircularLinkedList<string>& aList);
//template ostream& operator<<(ostream& out, const CircularLinkedList<cv::VideoCapture>& aList);