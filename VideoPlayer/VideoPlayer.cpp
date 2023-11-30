// VideoPlayer.cpp
#include "VideoPlayer.h"
#include <string>

VideoPlayer::VideoPlayer() : paused(false) {}

void VideoPlayer::add_Video(string videoPath) {
    playlist.insert(videoPath, playlist.getSize());
}

void VideoPlayer::removeVideo(int index) {
    if (index < 0 || index >= playlist.getSize()) {
        cerr << "Invalid index for removing video." << endl;
        return;
    }

    playlist.erase(index);
    cout << "Removed video at index " << index << endl;
}

void VideoPlayer::playPlaylist() {
    if (playlist.empty()) {
        cout << "Playlist is empty." << endl;
        return;
    }

    cout << "Playing playlist..." << endl;

    while (!playlist.empty()) {
        string videoPath = playlist.getCurrentData();
        VideoCapture video(videoPath);
        if (!video.isOpened()) {
            cerr << "Error opening video file." << endl;
            return;
        }
        double fps = video.get(CAP_PROP_FPS);
        int originalWidth = video.get(CAP_PROP_FRAME_WIDTH);
        int originalHeight = video.get(CAP_PROP_FRAME_HEIGHT);
        namedWindow("Video Player", WINDOW_NORMAL);
        resizeWindow("Video Player", originalWidth, originalHeight);
        Mat frame;
        while (true) {
            if (!paused) {
                if (!video.read(frame)) {
                    break;
                }
                imshow("Video Player", frame);
            }

            char c = (char) waitKey(1000 / static_cast<int>(fps));
            if (c == 27) {
                cout << "Escape key pressed. Exiting..." << endl;
                exit(0);
            }
            else if (c == ' ') {
                paused = !paused;
            }
            else if (c == 'n') {
                playNextVideo();
                break;
            } else if (c == 'p') {
                playPreviousVideo();
                break;
            }
            else if (c == 'a') {
                addVideoRuntime();
                break;
            }
            else if (c == 'r') {
                removeVideoRuntime();
                break;
            }
            else if (c == 's') {
                stopPlaylist();
                break;
            }
        }

        video.release();
    }
}

void VideoPlayer::playNextVideo() {
    cout << "Playing next video..." << endl;
    paused = false;
    playlist.rotateNext();
}

void VideoPlayer::playPreviousVideo() {
    cout << "Playing previous video..." << endl;
    paused = false;
    playlist.rotatePrevious();
}

void VideoPlayer::addVideoRuntime() {
    string videoPath;
    cout << "Enter the path of the video to add: ";
    getline(cin, videoPath);
    cout << videoPath;
    add_Video(videoPath.substr(1, videoPath.length() - 2));
}

void VideoPlayer::removeVideoRuntime() {
    int index;
    cout << "Enter the index of the video to remove: ";
    cin >> index;
    if (index == playlist.search(playlist.getCurrentData())) {
        playNextVideo();
    }
    removeVideo(index);
}

void VideoPlayer::stopPlaylist() {
    playlist.clear();
    paused = false;
    cout << "Playlist stopped." << endl;
}

CircularLinkedList<string> VideoPlayer::getPlaylist() {
    return playlist;
}
