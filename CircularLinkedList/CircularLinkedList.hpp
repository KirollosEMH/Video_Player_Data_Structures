#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

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

    /*
     * Default constructor
     * Initializes the list to an empty state.
    */

    CircularLinkedList(const CircularLinkedList& origList);

    /*
     * Copy constructor
     * Initializes the list to be equivalent to the other CircularLinkedList object parameter.
     * @param origList the CircularLinkedList object to copy
    */

    ~CircularLinkedList();

    /*
     * Destructor
     * Frees the memory used by the list.
    */

    const CircularLinkedList& operator=(const CircularLinkedList& rightSide);

    /*
     * Overloaded assignment operator
     * Sets the list to be equivalent to the other CircularLinkedList object parameter and returns a reference to this object.
     * @param rightSide the CircularLinkedList object to copy
     * @return a reference to this CircularLinkedList object
    */

    bool empty() const;

    /*
     * Tests whether the list is empty.
     * @return true if the list is empty, false otherwise
    */

    void insert(ElementType dataVal, int pos);

    /*
     * Inserts dataVal into the list so that it appears at the position given by the zero-based pos value.
     * @param dataVal the data value to insert into the list
     * @param pos the position in the list to insert the data value
    */

    void erase(int index);

    /*
     * Removes the element at the position given by the zero-based index value.
     * @param index the position in the list of the element to remove
    */

    int search(ElementType dataVal);

    /*
     * Searches the list for dataVal.
     * @param dataVal the data value to search for
     * @return the position in the list of the data value, -1 if not found
    */

    void display(ostream& out) const;

    /*
     * Outputs to the stream out all of the data values stored in the list, each value separated by a space.
     * @param out the ostream object to output to
    */

    int getSize() const;

    /*
     * @return the number of elements in the list
    */

    void rotateNext();

    /*
     * Moves the current pointer to the next element in the list.
    */

    void rotatePrevious();

    /*
     * Moves the current pointer to the previous element in the list.
    */

    ElementType getCurrentData() const;

    /*
     * @return the data value stored in the element pointed to by the current pointer
    */

    void clear();

    /*
     * Removes all elements from the list.
    */

    void organizeBySwap(int old_pos, int pos);

    /*
     * Organizes the list by swapping the element at the position given by the zero-based pos value with the element containing dataVal.
     * @param dataVal the data value to search for
     * @param pos the position in the list of the element to move
    */

    void organizeByShift(int old_pos, int pos);

    /*
     * Organizes the list by shifting the element at the position given by the zero-based pos value to the position immediately after the element containing dataVal.
     * @param dataVal the data value to search for
     * @param pos the position in the list of the element to move
    */

    void displayVideoNames(ostream& out) const;

    /*
     * Outputs to the stream out all of the data values stored in the list, each value separated by a space.
     * @param out the ostream object to output to
    */

    ElementType getIndexValue(int index) const;

};



template <typename ElementType>
ostream& operator<<(ostream& out, const CircularLinkedList<ElementType>& aList);

#endif // CIRCULAR_LINKED_LIST
