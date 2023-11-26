#ifndef TESTPROJECT_VIDEOPLAYER_H
#define TESTPROJECT_VIDEOPLAYER_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include "../CircularLinkedList/CircularLinkedList.hpp"
#include <string>

using namespace cv;
using namespace std;

class VideoPlayer {
private:
    CircularLinkedList<string> playlist;
    bool paused;

public:
    VideoPlayer();

    void add_Video(string videoPath);

    void removeVideo(int index);

    void playPlaylist();

    void playNextVideo();

    void playPreviousVideo();

    void addVideoRuntime();

    void removeVideoRuntime();

    void stopPlaylist();

    CircularLinkedList<string> getPlaylist();
};
#endif //TESTPROJECT_VIDEOPLAYER_H
