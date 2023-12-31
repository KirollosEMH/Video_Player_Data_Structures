#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include "../CircularLinkedList/CircularLinkedList.hpp"
#include <string>
#include <vector>

using namespace cv;
using namespace std;

class VideoPlayer {
private:
    class Playlist {
    public:
        CircularLinkedList<string> videos;
        string PlayListName;

        void addVideo(const string& videoPath) {
            videos.insert(videoPath, videos.getSize());
        }

        void removeVideo(int index) {
            if (index >= 0 && index < videos.getSize()) {
                videos.erase(index);
                cout << "Removed video at index " << index << endl;
            } else {
                cerr << "Invalid index for removing video." << endl;
            }
        }

        void clear() {
            videos.clear();
        }
    };

    vector<Playlist> playlists;
    Playlist* currentPlaylist;
    bool paused;

public:
    VideoPlayer();

    void readDatabase();

    void writeDatabase();

    void VideoPlayerMainMenu();

    void createPlaylist();

    void deletePlaylist();

    void selectPlaylist();

    void addVideo(const string& videoPath);

    void removeVideo(int index);

    void playPlaylist();

    void playNextVideo();

    void playPreviousVideo();

    void addVideoRuntime();

    void removeVideoRuntime();

    void organizeVideos(int choice, int old_pos, int index);

    void displayvideos();

    void displayPlaylists();

    void displayVideoDetails();

    CircularLinkedList<string> getCurrentPlaylist();

    vector<Playlist> getPlaylists();
};

#endif // VIDEOPLAYER_H
