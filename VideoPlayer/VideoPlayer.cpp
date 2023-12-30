// VideoPlayer.cpp
#include "VideoPlayer.h"
#include <string>
#include <fstream>
#define CVUI_IMPLEMENTATION
#include "../cvui.h"


VideoPlayer::VideoPlayer() : paused(false), currentPlaylist(nullptr) {
    readDatabase();
}

void VideoPlayer::readDatabase() {
    std::ifstream database("../DB/Playlists.csv");
    if (!database.is_open()) {
        std::cerr << "Error opening Playlist.csv" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(database, line)) {
        Playlist newPlaylist;

        // Use stringstream to parse the line
        std::istringstream ss(line);
        std::string token;

        // First token is the playlist name
        if (std::getline(ss, token, ',')) {
            newPlaylist.PlayListName = token;
        } else {
            std::cerr << "Error parsing playlist name in line: " << line << std::endl;
            continue;  // Skip this line and move to the next one
        }

        // Remaining tokens are video paths
        while (std::getline(ss, token, ',')) {
            newPlaylist.addVideo(token);
        }

        // Add the new playlist to the playlists vector
        playlists.push_back(newPlaylist);
    }

    database.close();
}

void VideoPlayer::writeDatabase() {
    ofstream database("../DB/Playlists.csv");
    if (!database.is_open()) {
        cerr << "Error opening Playlist.csv" << std::endl;
        return;
    }

    for (const Playlist& playlist : playlists) {
        database << playlist.PlayListName;
        for (int i = 0; i < playlist.videos.getSize(); ++i) {
            database << "," << playlist.videos.getIndexValue(i);
        }
        database << std::endl;
    }

    database.close();
}


void VideoPlayer::VideoPlayerMainMenu() {
    char choice;
    cvui::init("Video Player Menu");

    cv::Mat frame = cv::Mat(500, 1000, CV_8UC3);

    int x = 250;
    int y = 25;

    while (true) {
        // Clear the frame
        frame = cv::Scalar(200, 200, 200);

        cvui::text(frame, 280, 25, "Video Player Menu", 1.5, 0x000000);

        int buttonHeight = 40;  // Initial height of the button
        int buttonWidth = 500;  // Initial width of the button
        int buttonColor = 0x888888;  // Color for the buttons
        float fontSize = 0.5;  // Font size for the buttons



        // First button with different font size and color
        if (cvui::button(frame, x, y + buttonHeight * 1,buttonWidth,buttonHeight, "Create Playlist")) {
            createPlaylist();
        }

        // Remaining buttons with the same style
        if (cvui::button(frame, x, y + buttonHeight * 2,buttonWidth,buttonHeight,  "Delete Playlist")) {

            displayPlaylists();
            std::cout << "Enter the index of the playlist to delete: ";
            int deleteIndex;
            std::cin >> deleteIndex;
            deletePlaylist(deleteIndex - 1);  // Adjust for 1-based index
        }

        if (cvui::button(frame, x, y + buttonHeight * 3,buttonWidth,buttonHeight,  "Select Playlists")) {
            int selectIndex = 1;
            string selectPlaylistStr;
            while (true) {
                // Clear the frame
                frame = cv::Scalar(200, 200, 200);

                cvui::text(frame, 350, 25, "Select Playlist", 1.5, 0x000000);

                for (size_t i = 0; i < playlists.size(); ++i) {
                    string text = to_string(i + 1) + ". " + playlists[i].PlayListName;
                    cvui::text(frame, 50, 100 + 25 * i, text , 0.5, 0x000000);
                }

                cvui::input(frame, 50, 100 + 25 * playlists.size(), 200, "Video Number", selectPlaylistStr);

                if (cvui::button(frame, 50, 100 + 25 * playlists.size() + 50, 200, 50, "Select Playlist")) {
                    break;
                }
                // Update the cvui components
                cvui::update();

                // Show the frame
                cv::imshow("Video Player Menu", frame);

                // Check for keypress
                choice = cv::waitKey(20);
            }
            try {
                selectIndex = stoi(selectPlaylistStr);
                selectPlaylist(selectIndex - 1);
            } catch (std::invalid_argument& e) {
                std::cerr << "Invalid input for playlist selection." << std::endl;
            }


        }

        if (cvui::button(frame, x, y + buttonHeight * 4,buttonWidth,buttonHeight,  "Play Selected Playlist")) {
            playPlaylist();
        }

        if (cvui::button(frame, x, y + buttonHeight * 5,buttonWidth,buttonHeight,  "Add Video to Playlist")) {
            addVideoRuntime();
        }

        if (cvui::button(frame, x, y + buttonHeight * 6,buttonWidth,buttonHeight,  "Remove Video from Playlist")) {
            removeVideoRuntime();
        }

        if (cvui::button(frame, x, y + buttonHeight * 7,buttonWidth,buttonHeight,  "Organize Videos")) {
            organizeVideos();
        }

        if (cvui::button(frame, x, y + buttonHeight * 8,buttonWidth,buttonHeight,  "Display Videos")) {
            displayvideos();
        }

        if (cvui::button(frame, x, y + buttonHeight * 9,buttonWidth,buttonHeight,  "Display Video Details")) {
            displayVideoDetails();
        }

        if (cvui::button(frame, x, y + buttonHeight * 10,buttonWidth,buttonHeight,  "Quit")) {
            writeDatabase();
            std::cout << "Exiting program." << std::endl;
            return;
        }

        // Update the cvui components
        cvui::update();

        // Show the frame
        cv::imshow("Video Player Menu", frame);

        // Check for keypress
        choice = cv::waitKey(20);
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

void VideoPlayer::organizeVideos() {
    int choice;
    cout << "Selected playlist: " << currentPlaylist->PlayListName << endl;
    displayvideos();
    cout << "Choose the method of organizing the videos: " << endl;
    cout << "1. Shifting" << endl;
    cout << "2. Swapping" << endl;
    cin >> choice;
    int old_pos;

    cout << "Enter the video to organize: \n";
    cin >> old_pos;
    int index;
    cout << "Enter the new position of the video: \n";

    cin >> index;

    switch (choice) {
        case 1:
            cout << "Shifting Operation is applied" << endl;
            currentPlaylist -> videos.organizeByShift(old_pos-1, index-1);
            break;
        case 2:
            cout << "Swapping" << endl;
            currentPlaylist -> videos.organizeBySwap(old_pos-1, index-1);
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
    }
}

void VideoPlayer::playPlaylist() {
    if (currentPlaylist == nullptr){
        cout << "No playlist selected. Please select a playlist first." << endl;
        return;
    }
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
            if (c == 27 || c=='s') {
                video.release();
                destroyWindow("Video Player");
                return;
            } else if (c == ' ') {
                paused = !paused;
            } else if (c == 'n' || c == 77) {
                playNextVideo();
                break;
            } else if (c == 'p' || c == 75) {
                playPreviousVideo();
                break;
            } else if (c == 'r') {
                removeVideoRuntime();
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
        //cout << videoPath;
        addVideo(videoPath);
    } else {
        cerr << "No playlist selected. Please select a playlist first." << endl;
    }
}

void VideoPlayer::removeVideoRuntime() {
    if (currentPlaylist) {
        cout << "Selected playlist: " << currentPlaylist->PlayListName << endl;
        displayvideos();
        int index;
        cout << "Enter the Number of the video to remove: ";
        cin >> index;
        removeVideo(index-1);
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

void VideoPlayer::displayvideos() {
    if (currentPlaylist) {
        currentPlaylist->videos.displayVideoNames(cout);
    } else {
        cerr << "No playlist selected. Please select a playlist first." << endl;
    }
}

void VideoPlayer::displayVideoDetails() {
    if (currentPlaylist) {
        displayvideos();
        int index;
        cout << "Enter the index of the video to display details: ";
        cin >> index;
        string videoPath = currentPlaylist->videos.getIndexValue(index - 1);


        VideoCapture video(videoPath);

        if (!video.isOpened()) {
            cerr << "Error opening video file: " << videoPath << endl;
            return;
        }

        double fps = video.get(CAP_PROP_FPS);
        int frameCount = int(video.get(CAP_PROP_FRAME_COUNT));
        int width = int(video.get(CAP_PROP_FRAME_WIDTH));
        int height = int(video.get(CAP_PROP_FRAME_HEIGHT));
        double duration = frameCount / fps;

        cout << "Video: " << videoPath << endl;
        cout << "Duration: " << duration << " seconds" << endl;
        cout << "Frame Count: " << frameCount << endl;
        cout << "Width: " << width << " px, Height: " << height << " px" << endl;
        cout << "Frame Rate: " << fps << " FPS" << endl;

        video.release();
    } else {
        cerr << "No playlist selected. Please select a playlist first." << endl;
    }
}