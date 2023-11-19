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
    
}

void CircularLinkedList::display(ostream& out) const
{
    
}

ostream& operator<<(ostream& out, const CircularLinkedList& aList)
{
    
}