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

    // copy constructor test
    CircularLinkedList<int> list2(list1);
    cout << "list2 after copy constructor: " << endl;
    list2.display(cout);

    // assignment operator test
    CircularLinkedList<int> list3;
    list3 = list1;
    cout << "list3 after assignment operator: " << endl;
    list3.display(cout);

    // erase test
    cout << "list3 before erasing index(0): " << endl;
    list3.display(cout);
    list3.erase(0);
    list3.display(cout);

    // search test
    cout << "Index of 3 in list3:  " << list3.search(3) << endl;

    // organizeBySwap test
    cout << "list3 before organizeBySwap: " << endl;
    list3.display(cout);
    list3.organizeBySwap(3,0);
    list3.display(cout);

    // organizeByShift test
    cout << "list3 before organizeByShift: " << endl;
    list3.display(cout);
    list3.organizeByShift(4,0);
    list3.display(cout);

    // size test
    cout << "Size of list3: " << list3.getSize() << endl;

    // clear test
    cout << "list3 before clear: " << endl;
    list3.display(cout);
    list3.clear();
    list3.display(cout);

    CircularLinkedList <int> list4;
    list4 = list3;
    cout << "list4 after assignment operator: " << endl;
    list4.display(cout);

    // empty test
    cout << "list3 empty? " << list3.empty() << endl;

    // destructor test
    list1.~CircularLinkedList();

    // getCurrent test
    cout << "list2: " << endl;
    list2.display(cout);
    cout << "list2 current data: ";
    cout << list2.getCurrentData() << endl;

    // rotateNext test
    cout << "list2 current data after rotateNext: ";
    list2.rotateNext();
    cout << list2.getCurrentData() << endl;

    // rotatePrev test
    cout << "list2 current data after rotatePrev: ";
    list2.rotatePrevious();
    cout << list2.getCurrentData() << endl;

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