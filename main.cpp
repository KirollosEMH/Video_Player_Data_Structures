#include "CircularLinkedList/CircularLinkedList.hpp"
#include "VideoPlayer/VideoPlayer.h"
#include<opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main(){
    VideoPlayer player;

    // Add videos to the playlist
    player.add_Video("D:/ASU/5 Fall 23/Data Structures/TestProject/video2.mp4");
    player.add_Video("D:/ASU/5 Fall 23/Data Structures/TestProject/video3.mp4");
    player.add_Video("D:/ASU/5 Fall 23/Data Structures/TestProject/video4.mp4");

    player.getPlaylist().display(cout);
    cout << player.getPlaylist().search("D:/ASU/5 Fall 23/Data Structures/TestProject/video4.mp4") << endl;

    // Play the playlist
    player.playPlaylist();


//    CircularLinkedList<int> list1;
//    list1.insert(1, 0);
//    list1.insert(2, 1);
//    list1.insert(2, 0);
//    list1.insert(3, 2);
//    list1.insert(4, 3);
//    list1.insert(4, 3);
//    list1.insert(5, 4);
//
//    CircularLinkedList<int> list2(list1);
//    CircularLinkedList<int> list3;
//    list3 = list2;
//
//    cout << "List1: " << list1;
//    cout << "List2: " << list2;
//
//    list3.erase(0);
//    list3.erase(0);
//    list3.erase(0);
//    cout << "List3: " << list3;
//
//    list2.erase(0);
//    list2.erase(2);
//    list2.erase(4);
//    list2.erase(-10);
//    cout << "List2: " << list2;
//
//    list1.erase(6);
//    cout << "List1: " << list1;
//
//    cout << "List1 value 4 at location: " << list1.search(4) << endl;
//    cout << "List1 value 5 at location: " << list1.search(5) << endl;
//    cout << "List1 value 6 at location: " << list1.search(6) << endl;
//
//    list2.erase(0);
//    list2.erase(0);
//    list2.erase(0);
//    list2.erase(0);
//    cout << "List2: " << list2;
//
//    cout << "List2 value 4 at location: " << list2.search(4) << endl;

    return 0;
}