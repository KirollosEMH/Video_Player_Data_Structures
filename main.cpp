#include "CircularLinkedList/CircularLinkedList.hpp"
#include "VideoPlayer/VideoPlayer.h"
#include<opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#define CIRCULAR_TEST

int main(){
#ifdef CIRCULAR_TEST
    // default constructor test
    CircularLinkedList<int> list1;

    // insert test
    list1.insert(1, 0);
    list1.insert(2, 1);
    list1.insert(3, 2);
    list1.insert(4, 3);
    cout << "list1 after insert: " << endl;
    list1.display(cout);
    cout << "=============================" << endl;

    // copy constructor test
    CircularLinkedList<int> list2(list1);
    cout << "list2 after copy constructor: " << endl;
    list2.display(cout);
    cout << "=============================" << endl;

    // assignment operator test
    CircularLinkedList<int> list3, list4, list5;
    list3 = list1;
    cout << "list3 after assignment operator: " << endl;
    list3.display(cout);
    cout << "=============================" << endl;

    // erase test
    cout << "list3 before erasing index(0): " << endl;
    list3.display(cout);
    list3.erase(0);
    cout << "list3 after erasing index(0): " << endl;
    list3.display(cout);
    cout << "=============================" << endl;

    // erase test exception
    cout << "list3 before erasing index(125): " << endl;
    list3.display(cout);
    list3.erase(125);
    cout << "list3 after erasing index(125): " << endl;
    list3.display(cout);
    cout << "=============================" << endl;

    // assignment operator test
    list4 = list5 = list3;
    cout << "list4 after assignment operator: " << endl;
    list4.display(cout);
    cout << "list5 after assignment operator: " << endl;
    list5.display(cout);
    cout << "=============================" << endl;

    // search test
    cout << "Index of 3 in list3:  " << list3.search(3) << endl;

    // search test exception
    cout << "Index of 125 in list3:  " << list3.search(125) << endl;
    cout << "=============================" << endl;

    // organizeBySwap test
    cout << "list3 before organizeBySwap (value of 3 to position 0): " << endl;
    list3.display(cout);
    cout << "list3 after organizeBySwap (value of 3 to position 0): " << endl;
    list3.organizeBySwap(3,0);
    list3.display(cout);
    cout << "=============================" << endl;

    // organizeByShift test
    cout << "list3 before organizeByShift (value of 4 to position 0): " << endl;
    list3.display(cout);
    cout << "list3 after organizeByShift (value of 4 to position 0): " << endl;
    list3.organizeByShift(4,0);
    list3.display(cout);
    cout << "=============================" << endl;

    // organizeBySwap test exception
    cout << "list3 before organizeBySwap exception (value of 3 to position -1): " << endl;
    list3.display(cout);
    cout << "list3 after organizeBySwap exception (value of 3 to position -1): " << endl;
    list3.organizeBySwap(3,-1);
    list3.display(cout);
    cout << "=============================" << endl;

    // organizeByShift test exception
    cout << "list3 before organizeByShift exception (value of 3 to position 3): " << endl;
    list3.display(cout);
    cout << "list3 after organizeByShift exception (value of 3 to position 3): " << endl;
    list3.organizeByShift(3,3);
    list3.display(cout);
    cout << "=============================" << endl;

    // size test
    cout << "Size of list3: " << list3.getSize() << endl;
    cout << "=============================" << endl;

    // clear test
    cout << "list3 before clear: " << endl;
    list3.display(cout);
    list3.clear();
    cout << "list3 after clear: " << endl;
    list3.display(cout);
    cout << "=============================" << endl;

    string str = (list3.empty())? "Yes":"No";
    // empty test
    cout << "list3 empty? " << str << endl;
    cout << "=============================" << endl;

    cout << "list2 after Copy Constructor: " << endl;
    list2.display(cout);
    cout << "=============================" << endl;

    // destructor test
    list1.~CircularLinkedList();

    // getCurrent test
    cout << "list2: " << endl;
    list2.display(cout);
    cout << "list2 current data: ";
    cout << list2.getCurrentData() << endl;
    cout << "=============================" << endl;

    // rotateNext test
    cout << "list2 current data after rotateNext: ";
    list2.rotateNext();
    cout << list2.getCurrentData() << endl;
    cout << "=============================" << endl;

    // rotatePrev test
    cout << "list2 current data after rotatePrev: ";
    list2.rotatePrevious();
    cout << list2.getCurrentData() << endl;
    cout << "=============================" << endl;

    // creating a list of another type
    cout << "Creating a list of another type:" << endl;
    CircularLinkedList<string> list6;
    list6.insert("Hello", 0);
    list6.insert("World", 1);
    list6.insert("!", 2);
    cout << "list6 of string type: " << endl;
    list6.display(cout);
    cout << "=============================" << endl;

#else
    VideoPlayer player;

    // Add videos to the playlist
    player.add_Video("../Videos/video2.mp4");
    player.add_Video("../Videos/video3.mp4");
    player.add_Video("../Videos/video4.mp4");

    player.getPlaylist().display(cout);
    cout << player.getPlaylist().search("../Videos/video4.mp4") << endl;

    // Play the playlist
    player.playPlaylist();
    return 0;
#endif
}