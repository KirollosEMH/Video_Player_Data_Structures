// VideoPlayer.cpp
#include "VideoPlayer.h"
#include <string>

VideoPlayer::VideoPlayer() : paused(false), currentPlaylist(nullptr) {
    // Create a default playlist when the VideoPlayer is constructed.
    createPlaylist();
}

void VideoPlayer::VideoPlayerMainMenu() {
    char choice;
    while (true) {
        cout << "========== Video Player Main Menu ==========" << endl;
        cout << "1. Playlist Menu" << endl;
        cout << "2. Quit Program" << endl;
        cout << "============================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Consume newline character

        switch (choice) {
            case '1':
                PlaylistMenu();
                break;
            case '2':
                cout << "Exiting program." << endl;
                return;
            default:
                cerr << "Invalid choice. Try again." << endl;
        }
    }
}

void VideoPlayer::PlaylistMenu() {
    char choice;
    while (true) {
        cout << "============= Playlist Menu ==============" << endl;
        cout << "1. Create Playlist" << endl;
        cout << "2. Delete Playlist" << endl;
        cout << "3. Select Playlist" << endl;
        cout << "4. Play Playlist" << endl;
        cout << "5. Add Video to Playlist" << endl;
        cout << "6. Remove Video from Playlist" << endl;
        cout << "S. Stop Playlist" << endl;
        cout << "B. Back to Main Menu" << endl;
        cout << "==========================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Consume newline character

        switch (toupper(choice)) {
            case '1':
                createPlaylist();
                break;
            case '2':
                displayPlaylists();
                cout << "Enter the index of the playlist to delete: ";
                int deleteIndex;
                cin >> deleteIndex;
                deletePlaylist(deleteIndex - 1);  // Adjust for 1-based index
                break;
            case '3':
                displayPlaylists();
                cout << "Enter the index of the playlist to select: ";
                int selectIndex;
                cin >> selectIndex;
                selectPlaylist(selectIndex - 1);  // Adjust for 1-based index
                break;
            case '4':
                playPlaylist();
                break;
            case '5':
                addVideoRuntime();
                break;
            case '6':
                removeVideoRuntime();
                break;
            case 'S':
                stopPlaylist();
                break;
            case 'B':
                return;  // Back to the main menu
            default:
                cerr << "Invalid choice. Try again." << endl;
        }
    }
}

void VideoPlayer::addVideo(const string& videoPath) {
    if (currentPlaylist) {
        currentPlaylist->addVideo(videoPath);
    } else {
        cerr << "No playlist selected. Please select a playlist first." << endl;
    }
}

void VideoPlayer::removeVideo(int index) {
    if (currentPlaylist) {
        currentPlaylist->removeVideo(index);
    } else {
        cerr << "No playlist selected. Please select a playlist first." << endl;
    }
}

// Assuming the necessary headers are included and namespaces are used.

void VideoPlayer::playPlaylist() {
    if (currentPlaylist->videos.empty()) {
        cout << "Playlist is empty." << endl;
        return;
    }

    cout << "Playing playlist..." << endl;

    while (!currentPlaylist->videos.empty()) {
        string videoPath = currentPlaylist->videos.getCurrentData();
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

            char c = (char)waitKey(1000 / static_cast<int>(fps));
            if (c == 27) {
                cout << "Escape key pressed. Exiting..." << endl;
                exit(0);
            } else if (c == ' ') {
                paused = !paused;
            } else if (c == 'n' || c == 83) {
                playNextVideo();
                break;
            } else if (c == 'p' || c == 81) {
                playPreviousVideo();
                break;
            } else if (c == 'a') {
                addVideoRuntime();
                break;
            } else if (c == 'r') {
                removeVideoRuntime();
                break;
            } else if (c == 's') {
                stopPlaylist();
                break;
            }
        }

        video.release();
    }
}



void VideoPlayer::playNextVideo() {
    if (currentPlaylist) {
        cout << "Playing next video..." << endl;
        paused = false;
        currentPlaylist->videos.rotateNext();
    } else {
        cerr << "No playlist selected. Please select a playlist first." << endl;
    }
}

void VideoPlayer::playPreviousVideo() {
    if (currentPlaylist) {
        cout << "Playing previous video..." << endl;
        paused = false;
        currentPlaylist->videos.rotatePrevious();
    } else {
        cerr << "No playlist selected. Please select a playlist first." << endl;
    }
}

void VideoPlayer::addVideoRuntime() {
    if (currentPlaylist) {
        string videoPath;
        cout << "Enter the path of the video to add: ";
        getline(cin, videoPath);
        addVideo(videoPath);
    } else {
        cerr << "No playlist selected. Please select a playlist first." << endl;
    }
}

void VideoPlayer::removeVideoRuntime() {
    if (currentPlaylist) {
        int index;
        cout << "Enter the index of the video to remove: ";
        cin >> index;
        removeVideo(index);
    } else {
        cerr << "No playlist selected. Please select a playlist first." << endl;
    }
}

void VideoPlayer::stopPlaylist() {
    if (currentPlaylist) {
        currentPlaylist->clear();
        paused = false;
        cout << "Playlist stopped." << endl;
    } else {
        cerr << "No playlist selected. Please select a playlist first." << endl;
    }
}

CircularLinkedList<string> VideoPlayer::getCurrentPlaylist() {
    if (currentPlaylist) {
        return currentPlaylist->videos;
    } else {
        cerr << "No playlist selected. Returning an empty playlist." << endl;
        return CircularLinkedList<string>();  // Return an empty playlist
    }
}

vector<VideoPlayer::Playlist> VideoPlayer::getPlaylists() {
    return playlists;
}

void VideoPlayer::createPlaylist() {
    Playlist newPlaylist;
    cout << "Enter the name for the new playlist: ";
    getline(cin, newPlaylist.PlayListName);
    playlists.push_back(newPlaylist);
    cout << "Playlist '" << newPlaylist.PlayListName << "' created." << endl;
}

void VideoPlayer::deletePlaylist(int index) {
    if (index >= 0 && index < playlists.size()) {
        playlists.erase(playlists.begin() + index);
        cout << "Playlist at index " << index << " deleted." << endl;
        if (!playlists.empty()) {
            selectPlaylist(0);
        } else {
            currentPlaylist = nullptr;
        }
    } else {
        cerr << "Invalid index for deleting playlist." << endl;
    }
}

void VideoPlayer::selectPlaylist(int index) {
    if (index >= 0 && index < playlists.size()) {
        currentPlaylist = &playlists[index];
        cout << "Playlist '" << playlists[index].PlayListName << "' selected." << endl;
    } else {
        cerr << "Invalid index for selecting playlist." << endl;
    }
}

void VideoPlayer::displayPlaylists() {
    cout << "Available Playlists:" << endl;
    for (size_t i = 0; i < playlists.size(); ++i) {
        cout << i + 1 << ". " << playlists[i].PlayListName << endl;
    }
}