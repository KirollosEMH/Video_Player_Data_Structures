// VideoPlayer.cpp
#include "VideoPlayer.h"
#include <string>
#include <fstream>
#include <nfd.h>
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
            deletePlaylist();
        }

        if (cvui::button(frame, x, y + buttonHeight * 3,buttonWidth,buttonHeight,  "Select Playlists")) {
            selectPlaylist();
        }

        if (cvui::button(frame, x, y + buttonHeight * 4,buttonWidth,buttonHeight,  "Play Selected Playlist")) {
            if(currentPlaylist){
                playPlaylist();
            }
            else{
                while (true) {
                    // Clear the frame
                    frame = cv::Scalar(200, 200, 200);

                    cvui::text(frame, 350, 25, "Videos Available", 1.5, 0x000000);

                    cvui::text(frame, 50, 100, "No playlist selected! press q", 0.8, 0x000000);
                    // Update the cvui components
                    cvui::update();

                    // Show the frame
                    cv::imshow("Video Player Menu", frame);

                    // Check for keypress
                    choice = cv::waitKey(20);
                    if (choice == 'q') {
                        break;
                    }
                }
            }
        }

        if (cvui::button(frame, x, y + buttonHeight * 5,buttonWidth,buttonHeight,  "Add Video to Playlist")) {
            addVideoRuntime();
        }

        if (cvui::button(frame, x, y + buttonHeight * 6,buttonWidth,buttonHeight,  "Remove Video from Playlist")) {
            removeVideoRuntime();
        }

        if (cvui::button(frame, x, y + buttonHeight * 7,buttonWidth,buttonHeight,  "Organize Videos")) {
            organizeVideosRuntime();
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

void VideoPlayer::organizeVideosRuntime() {
    if (currentPlaylist) {
        int choice_operation=-1 , old_pos , index,succesful=0;
        string choiceStr, old_posStr, indexStr;
        char choice;
        cv::Mat frame = cv::Mat(500, 1000, CV_8UC3);
        while (true) {
            // Clear the frame
            frame = cv::Scalar(200, 200, 200);

            cvui::text(frame, 350, 25, "Organize Videos", 1.5, 0x000000);
            cvui::text(frame, 300, 100, currentPlaylist ->PlayListName, 0.5, 0x000000);
            for (int i = 0; i < currentPlaylist->videos.getSize(); ++i) {
                string text =  currentPlaylist->videos.getIndexValue(i);
                text= text.substr(text.find_last_of(  '/') + 1);
                text = text.substr(text.find_last_of(  '\\') + 1);
                text = to_string(i + 1) + ". " + text;
                cvui::text(frame, 300, 100 + 25 * (i+1), text , 0.5, 0x000000);
            }

            cvui::text(frame, 50, 100, "Choice", 0.5, 0x000000);
            cvui::text(frame, 50, 125, "1. Shifting", 0.5, 0x000000);
            cvui::text(frame, 50, 150, "2. Swapping", 0.5, 0x000000);
            cvui::input(frame, 50, 175, 200, "Choice", choiceStr);

            /* cvui::text(frame, 50, 200, "Old Position", 0.5, 0x000000);
            cvui::input(frame, 50, 250, 200, "Old Position", old_posStr);
            cvui::text(frame, 50, 300, "New Position", 0.5, 0x000000);
            cvui::input(frame, 50, 350, 200, "New Position", indexStr); */

            if (cvui::button(frame, 50, 225, 200, 50, "Organize Videos")) {
                break;
            }
            // Update the cvui components
            cvui::update();

            // Show the frame
            cv::imshow("Video Player Menu", frame);

            // Check for keypress
            choice = cv::waitKey(20);
            if (choice == 'q') {
                break;
            }

        }
        try {
            choice_operation = stoi(choiceStr);
            //old_pos = stoi(old_posStr);
            //index = stoi(indexStr);
            //organizeVideos(choice_operation, old_pos, index);
        } catch (std::invalid_argument& e) {
            std::cerr << "Invalid input for playlist selection." << std::endl;
        }
        while (choice_operation == 1 || choice_operation == 2) {
            frame = cv::Scalar(200, 200, 200);
            //cvui::text(frame, 350, 25, "Organize Videos", 1.5, 0x000000);
            cvui::text(frame, 300, 100, currentPlaylist ->PlayListName, 0.5, 0x000000);
            for (int i = 0; i < currentPlaylist->videos.getSize(); ++i) {
                string text =  currentPlaylist->videos.getIndexValue(i);
                text= text.substr(text.find_last_of(  '/') + 1);
                text = text.substr(text.find_last_of(  '\\') + 1);
                text = to_string(i + 1) + ". " + text;
                cvui::text(frame, 300, 100 + 25 * (i+1), text , 0.5, 0x000000);
            }

            if (choice_operation == 1){
                cvui::text(frame, 350, 25, "Shifting", 1.5, 0x000000);
                cvui::text(frame, 50, 100, "Old Position", 0.5, 0x000000);
                cvui::input(frame, 50, 150, 200, "Old Position", old_posStr);
                cvui::text(frame, 50, 200, "New Position", 0.5, 0x000000);
                cvui::input(frame, 50, 250, 200, "New Position", indexStr);
                if (cvui::button(frame, 50, 300, 200, 50, "Organize Videos")) {
                    break;
                }

            }
            else if (choice_operation == 2){
                cvui::text(frame, 350, 25, "Swapping", 1.5, 0x000000);
                cvui::text(frame, 50, 100, "Old Position", 0.5, 0x000000);
                cvui::input(frame, 50, 150, 200, "Old Position", old_posStr);
                cvui::text(frame, 50, 200, "New Position", 0.5, 0x000000);
                cvui::input(frame, 50, 250, 200, "New Position", indexStr);
                if (cvui::button(frame, 50, 300, 200, 50, "Organize Videos")) {
                    break;
                }



            }
            // Update the cvui components
            cvui::update();

            // Show the frame
            cv::imshow("Video Player Menu", frame);

            // Check for keypress
            choice = cv::waitKey(20);
            if (choice == 'q') {
                break;
            }

        }
        try {
            old_pos = stoi(old_posStr);
            index = stoi(indexStr);
            organizeVideos(choice_operation, old_pos, index);
            succesful = 1;
        } catch (std::invalid_argument& e) {
            succesful = 0;
            std::cerr << "Invalid input for playlist selection." << std::endl;
        }
        cout << "Organized Videos" << endl;

        while (succesful == 1){

            frame = cv::Scalar(200, 200, 200);
            cvui::text(frame, 350, 25, "After Organizations", 1.5, 0x000000);
            cvui::text(frame, 300, 100, currentPlaylist ->PlayListName, 0.5, 0x000000);
            for (int i = 0; i < currentPlaylist->videos.getSize(); ++i) {
                string text =  currentPlaylist->videos.getIndexValue(i);
                text= text.substr(text.find_last_of(  '/') + 1);
                text = text.substr(text.find_last_of(  '\\') + 1);
                text = to_string(i + 1) + ". " + text;
                cvui::text(frame, 300, 100 + 25 * (i+1), text , 0.5, 0x000000);
            }
            if (cvui::button(frame, 250, 200, 200, 50, "Mainmenu")) {
                break;
            }
            // Update the cvui components
            cvui::update();

            // Show the frame
            cv::imshow("Video Player Menu", frame);

            // Check for keypress
            choice = cv::waitKey(20);
            if ( choice == 'q'){
                break;
            }

        }
    } else {
        char choice;
        cv::Mat frame = cv::Mat(500, 1000, CV_8UC3);
        while (true) {
            // Clear the frame
            frame = cv::Scalar(200, 200, 200);

            cvui::text(frame, 350, 25, "Videos Available", 1.5, 0x000000);

            cvui::text(frame, 50, 100, "No playlist selected! press q", 0.8, 0x000000);
            // Update the cvui components
            cvui::update();

            // Show the frame
            cv::imshow("Video Player Menu", frame);

            // Check for keypress
            choice = cv::waitKey(20);
            if (choice == 'q') {
                break;
            }
        }
    }
}

void VideoPlayer::organizeVideos(int choice, int old_pos, int index) {
    // int choice;
    // cout << "Selected playlist: " << currentPlaylist->PlayListName << endl;
    // displayvideos();
    // cout << "Choose the method of organizing the videos: " << endl;
    // cout << "1. Shifting" << endl;
    // cout << "2. Swapping" << endl;
    // cin >> choice;
    // int old_pos;

    // cout << "Enter the video to organize: \n";
    // cin >> old_pos;
    // int index;
    //cout << "Enter the new position of the video: \n";

    // cin >> index;

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
            currentPlaylist->videos.erase(currentPlaylist->videos.getIndex(videoPath));
            continue;
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
        NFD_Init();

        nfdchar_t *outPath;
        nfdfilteritem_t filterItem = {"Videos", "mp4,mov,avi"};
        nfdresult_t result = NFD_OpenDialog(&outPath, &filterItem, 1, NULL);

        if (result == NFD_OKAY) {
            addVideo(outPath);
        } else if (result == NFD_CANCEL) {
            std::cout << "User pressed cancel." << std::endl;
        } else {
            std::cerr << "Error opening file dialog." << std::endl;
        }
        NFD_Quit();
    } else {
        char choice;
        cv::Mat frame = cv::Mat(500, 1000, CV_8UC3);
        while (true) {
            // Clear the frame
            frame = cv::Scalar(200, 200, 200);

            cvui::text(frame, 350, 25, "Videos Available", 1.5, 0x000000);

            cvui::text(frame, 50, 100, "No playlist selected! press q", 0.8, 0x000000);
            // Update the cvui components
            cvui::update();

            // Show the frame
            cv::imshow("Video Player Menu", frame);

            // Check for keypress
            choice = cv::waitKey(20);
            if (choice == 'q') {
                break;
            }
        }
    }
}

void VideoPlayer::removeVideoRuntime() {
    if (currentPlaylist){
        cv::Mat frame = cv::Mat(500, 1000, CV_8UC3);
        int videoIndex = 0;
        std::string indexStr;

        while (true) {
            frame = cv::Scalar(200, 200, 200);

            cvui::text(frame, 50, 50, "Remove Video from Playlist", 1.5, 0x000000);

            if (currentPlaylist) {
                // Display playlist name
                cvui::text(frame, 50, 100, "Playlist: " + currentPlaylist->PlayListName, 1.0, 0x000000);

                // Display indices and names of videos in the playlist
                for (size_t i = 0; i < currentPlaylist->videos.getSize(); ++i) {
                    string text =  currentPlaylist->videos.getIndexValue(i);
                    text= text.substr(text.find_last_of(  '/') + 1);
                    text = text.substr(text.find_last_of(  '\\') + 1);
                    text = to_string(i + 1) + ". " + text;
                    cvui::text(frame, 50, 150 + i * 30, text, 0.8, 0x000000);
                }

                // Input field for the video index to remove
                cvui::input(frame, 600, 150, 200, "Video Index", indexStr);
                if (!indexStr.empty()) {
                    try {
                        videoIndex = std::stoi(indexStr);

                    } catch (const std::invalid_argument& e) {
                        std::cerr << "Invalid input for video index: " << e.what() << std::endl;
                    }
                }
            } else {
                cvui::text(frame, 50, 100, "No playlist selected! press q", 0.8, 0x000000);
            }

            if (cvui::button(frame, 600, 200,200,50, "Remove Video")) {
                if (currentPlaylist) {
                    removeVideo(videoIndex - 1); // Adjust for 1-based index

                } else {
                    std::cerr << "No playlist selected. Please select a playlist first." << std::endl;
                }
            }

            if (cvui::button(frame, 750, 300,200,50, "Back")) {
                break;
            }



            // Update cvui and display frame
            cvui::update();
            cv::imshow("Video Player Menu", frame);

            char choice = cv::waitKey(20);
            if (choice == 'q') {
                break;
            }
        }
    }
    else {
        char choice;
        cv::Mat frame = cv::Mat(500, 1000, CV_8UC3);
        while (true) {
            // Clear the frame
            frame = cv::Scalar(200, 200, 200);

            cvui::text(frame, 350, 25, "Videos Available", 1.5, 0x000000);

            cvui::text(frame, 50, 100, "No playlist selected! press q", 0.8, 0x000000);
            // Update the cvui components
            cvui::update();

            // Show the frame
            cv::imshow("Video Player Menu", frame);

            // Check for keypress
            choice = cv::waitKey(20);
            if (choice == 'q') {
                break;
            }
        }
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
    //Playlist newPlaylist;
    //cout << "Enter the name for the new playlist: ";
    //getline(cin, newPlaylist.PlayListName);
    //playlists.push_back(newPlaylist);
    //cout << "Playlist '" << newPlaylist.PlayListName << "' created." << endl;
    cv::Mat frame = cv::Mat(500, 1000, CV_8UC3);
    string playlistName;
    while (true) {
        frame = cv::Scalar(200, 200, 200);

        cvui::text(frame, 250, 50, "Create Playlist", 1.5, 0x000000);

        cvui::input(frame, 50, 100, 200, "Playlist Name", playlistName);

        if (cvui::button(frame, 50, 200, 200, 50, "Create Playlist")) {
            break;
        }

        // Update cvui and display frame
        cvui::update();
        cv::imshow("Video Player Menu", frame);

        char choice = cv::waitKey(20);
        if (choice == 'q') {
            break;
        }

    }
    if (playlistName != ""){
        Playlist newPlaylist;
        newPlaylist.PlayListName = playlistName;
        playlists.push_back(newPlaylist);
    }
    //playlists.push_back(newPlaylist);
}

void VideoPlayer::deletePlaylist() {
    cv::Mat frame = cv::Mat(500, 1000, CV_8UC3);
    int index = 0;
    string indexStr;
    while (true){
        frame = cv::Scalar(200, 200, 200);

        cvui::text(frame, 250, 50, "Delete Playlist", 1.5, 0x000000);

        if (!playlists.empty()) {
            // Display playlist names
            for (size_t i = 0; i < playlists.size(); ++i) {
                string text = to_string(i + 1) + ". " + playlists[i].PlayListName;
                cvui::text(frame, 50, 100 + i * 30, text, 0.8, 0x000000);
            }
        } else {
            cvui::text(frame, 50, 100, "No playlists available! press q", 0.8, 0x000000);
        }

        cvui::input(frame, 50, 100+playlists.size() * 30, 200, "Playlist Index", indexStr);



        if (cvui::button(frame, 50, 100+playlists.size()*30 +50,200,40, "Delete Playlist")) {
            break;
        }

        // Update cvui and display frame
        cvui::update();
        cv::imshow("Video Player Menu", frame);

        char choice = cv::waitKey(20);
        if (choice == 'q') {
            break;
        }


    }
    try {
        index = stoi(indexStr);
        --index;  // Adjust for 1-based index
        if (index >= 0 && index < playlists.size()) {
            playlists.erase(playlists.begin() + index);
            if (!playlists.empty()) {
                currentPlaylist = &playlists[0];
            } else {
                currentPlaylist = nullptr;
            }
        } else {
            cerr << "Invalid index for deleting playlist." << endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid input for playlist index: " << e.what() << std::endl;
    }

}

void VideoPlayer::selectPlaylist() {
    int selectIndex = 1;
    string selectPlaylistStr;

    cv::Mat frame = cv::Mat(500, 1000, CV_8UC3);
    char choice;
    while (true) {
        // Clear the frame
        frame = cv::Scalar(200, 200, 200);

        cvui::text(frame, 350, 25, "Select Playlist", 1.5, 0x000000);

        for (size_t i = 0; i < playlists.size(); ++i) {
            string text = to_string(i + 1) + ". " + playlists[i].PlayListName;
            cvui::text(frame, 50, 100 + 25 * i, text , 0.8, 0x000000);
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
        if (choice == 'q') {
            break;
        }
    }
    try {
        selectIndex = stoi(selectPlaylistStr);
        selectIndex--;
        if (selectIndex >= 0 && selectIndex < playlists.size()) {
            currentPlaylist = &playlists[selectIndex];
            cout << "Playlist '" << playlists[selectIndex].PlayListName << "' selected." << endl;
        } else {
            cerr << "Invalid index for selecting playlist." << endl;
        }
    } catch (std::invalid_argument& e) {
        std::cerr << "Invalid input for playlist selection." << std::endl;
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
        char choice;
        cv::Mat frame = cv::Mat(500, 1000, CV_8UC3);
        while (true) {
            // Clear the frame
            frame = cv::Scalar(200, 200, 200);

            cvui::text(frame, 350, 25, "Videos Available", 1.5, 0x000000);

            for (int i = 0; i < currentPlaylist->videos.getSize(); ++i) {
                string text =  currentPlaylist->videos.getIndexValue(i);
                text= text.substr(text.find_last_of(  '/') + 1);
                text = text.substr(text.find_last_of(  '\\') + 1);
                text = to_string(i + 1) + ". " + text;
                cvui::text(frame, 50, 110 + i * 30, text, 0.8, 0x000000);
            }

            if (cvui::button(frame, 600, 100, 200, 50, "Back")) {
                break;
            }
            // Update the cvui components
            cvui::update();

            // Show the frame
            cv::imshow("Video Player Menu", frame);

            // Check for keypress
            choice = cv::waitKey(20);
            if (choice == 'q') {
                break;
            }
        }
    } else {
        char choice;
        cv::Mat frame = cv::Mat(500, 1000, CV_8UC3);
        while (true) {
            // Clear the frame
            frame = cv::Scalar(200, 200, 200);

            cvui::text(frame, 350, 25, "Videos Available", 1.5, 0x000000);

            cvui::text(frame, 50, 100, "No playlist selected! press q", 0.8, 0x000000);
            // Update the cvui components
            cvui::update();

            // Show the frame
            cv::imshow("Video Player Menu", frame);

            // Check for keypress
            choice = cv::waitKey(20);
            if (choice == 'q') {
                break;
            }
        }
    }
}

void VideoPlayer::displayVideoDetails() {
    if (currentPlaylist) {
//        displayvideos();
//        int index;
//        cout << "Enter the index of the video to display details: ";
//        cin >> index;
//        string videoPath = currentPlaylist->videos.getIndexValue(index - 1);
//
//
//        VideoCapture video(videoPath);
//
//        if (!video.isOpened()) {
//            cerr << "Error opening video file: " << videoPath << endl;
//            return;
//        }
//
//        double fps = video.get(CAP_PROP_FPS);
//        int frameCount = int(video.get(CAP_PROP_FRAME_COUNT));
//        int width = int(video.get(CAP_PROP_FRAME_WIDTH));
//        int height = int(video.get(CAP_PROP_FRAME_HEIGHT));
//        double duration = frameCount / fps;
//
//        cout << "Video: " << videoPath << endl;
//        cout << "Duration: " << duration << " seconds" << endl;
//        cout << "Frame Count: " << frameCount << endl;
//        cout << "Width: " << width << " px, Height: " << height << " px" << endl;
//        cout << "Frame Rate: " << fps << " FPS" << endl;
//
//        video.release();
        string displayVideoDetailsStr;
        int selectIndex = -1;
        char choice;
        cv::Mat frame = cv::Mat(500, 1000, CV_8UC3);
        while (true) {
            // Clear the frame
            frame = cv::Scalar(200, 200, 200);

            cvui::text(frame, 350, 25, "Videos Available", 1.5, 0x000000);

            for (int i = 0; i < currentPlaylist->videos.getSize(); ++i) {
                string text =  currentPlaylist->videos.getIndexValue(i);
                text= text.substr(text.find_last_of(  '/') + 1);
                text = text.substr(text.find_last_of(  '\\') + 1);
                text = to_string(i + 1) + ". " + text;
                cvui::text(frame, 50, 110 + i * 30, text, 0.8, 0x000000);
            }

            cvui::input(frame, 50, 110 + 30 * currentPlaylist->videos.getSize(), 200, "Video Number", displayVideoDetailsStr);

            if (cvui::button(frame, 50, 110 + 30 * currentPlaylist->videos.getSize() + 50, 200, 50, "Display Video Details")) {
                while (true) {
                    // Clear the frame
                    frame = cv::Scalar(200, 200, 200);

                    cvui::text(frame, 350, 25, "Video Details", 1.5, 0x000000);
                    try {
                        selectIndex = stoi(displayVideoDetailsStr);
                    } catch (std::invalid_argument& e) {
                        std::cerr << "Invalid input for playlist selection." << std::endl;
                    }

                    VideoCapture video(currentPlaylist->videos.getIndexValue(selectIndex - 1));
                    if (!video.isOpened()) {
                        break;
                    }


                    double fps = video.get(CAP_PROP_FPS);
                    int frameCount = int(video.get(CAP_PROP_FRAME_COUNT));
                    int width = int(video.get(CAP_PROP_FRAME_WIDTH));
                    int height = int(video.get(CAP_PROP_FRAME_HEIGHT));
                    double duration = frameCount / fps;


                    string text = currentPlaylist->videos.getIndexValue(selectIndex - 1);
                    text= text.substr(text.find_last_of(  '/') + 1);
                    text = text.substr(text.find_last_of(  '\\') + 1);

                    cvui::text(frame, 50, 100, "Video: " + text, 0.8, 0x000000);
                    cvui::text(frame, 50, 130, "Duration: " + to_string(duration) + " seconds", 0.8, 0x000000);
                    cvui::text(frame, 50, 160, "Frame Count: " + to_string(frameCount), 0.8, 0x000000);
                    cvui::text(frame, 50, 190, "Width: " + to_string(width) + " px, Height: " + to_string(height) + " px", 0.8, 0x000000);
                    cvui::text(frame, 50, 220, "Frame Rate: " + to_string(fps) + " FPS", 0.8, 0x000000);


                    if (cvui::button(frame, 600, 100, 200, 50, "Back")) {
                        break;
                    }
                    // Update the cvui components
                    cvui::update();

                    // Show the frame
                    cv::imshow("Video Player Menu", frame);

                    // Check for keypress
                    choice = cv::waitKey(20);
                    if (choice == 'q') {
                        break;
                    }
                }
            }

            if (cvui::button(frame, 50, 110 + 30 * currentPlaylist->videos.getSize() + 110, 200, 50, "Back")) {
                break;
            }
            // Update the cvui components
            cvui::update();

            // Show the frame
            cv::imshow("Video Player Menu", frame);

            // Check for keypress
            choice = cv::waitKey(20);
            if (choice == 'q') {
                break;
            }
        }


    } else {
        char choice;
        cv::Mat frame = cv::Mat(500, 1000, CV_8UC3);
        while (true) {
            // Clear the frame
            frame = cv::Scalar(200, 200, 200);

            cvui::text(frame, 350, 25, "Videos Available", 1.5, 0x000000);

            cvui::text(frame, 50, 100, "No playlist selected! press q", 0.8, 0x000000);
            // Update the cvui components
            cvui::update();

            // Show the frame
            cv::imshow("Video Player Menu", frame);

            // Check for keypress
            choice = cv::waitKey(20);
            if (choice == 'q') {
                break;
            }
        }
    }
}