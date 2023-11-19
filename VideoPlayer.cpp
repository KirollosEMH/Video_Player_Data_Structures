#include "CircularLinkedList.hpp"
//#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;


int main(){
    CircularLinkedList list1;
    list1.insert(1,0);
    list1.insert(2,1);
    list1.insert(2,0);
    list1.insert(3,2);
    list1.insert(4,3);
    list1.insert(4,3);
    list1.insert(5,4);
    CircularLinkedList list2(list1);
    CircularLinkedList list3;
    list3 = list2;
    cout << "List1: "<<list1;
    cout << "List2: "<<list2;
    list3.erase(0);
    list3.erase(0);
    list3.erase(0);
    cout <<"List3: "<< list3;  
    list2.erase(0);
    list2.erase(2);
    list2.erase(4);
    list2.erase(-10);
    cout << "List2: "<<list2;
    list1.erase(6);
    cout << "List1: "<< list1;
    return 0;
}
