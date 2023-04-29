cmake_minimum_required(VERSION 2.8)

project( image_corner_detection )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( image_corner_detection image_corner_detection.cpp )
target_link_libraries( image_corner_detection ${OpenCV_LIBS} )