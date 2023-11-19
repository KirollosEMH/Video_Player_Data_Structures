#include "CircularLinkedList.hpp"
//#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;


int main(){
    CircularLinkedList list;
    list.insert(1,0);
    list.insert(2,1);
    list.insert(2,0);
    list.insert(3,2);
    list.insert(4,3);
    list.insert(4,3);
    list.insert(5,4);
    CircularLinkedList list2(list);
    cout << list;
    cout << list2;  
    return 0;
}
