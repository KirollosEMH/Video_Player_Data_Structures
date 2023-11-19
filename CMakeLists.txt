cmake_minimum_required(VERSION 3.26)
project(Video_Player_Data_Structures)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


add_executable(Video_Player_Data_Structures
        CircularLinkedList.cpp
        CircularLinkedList.hpp)

target_link_libraries( Video_Player_Data_Structures ${OpenCV_LIBS})