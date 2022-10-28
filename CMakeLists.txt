#  minimum required cmake version: 3.1.0
cmake_minimum_required(VERSION 3.1.0)

project(Test)

find_library(REALSENSE2_FOUND realsense2 HINTS ${LIBRARY_DIR} REQUIRED)

# getting-started
add_executable(test test.cpp)
include_directories(test ${ADDITIONAL_INCLUDE_DIRS})
target_link_libraries(test ${REALSENSE2_FOUND})
set_target_properties (test PROPERTIES FOLDER Examples)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( test ${OpenCV_LIBS} )

install(
    TARGETS

    test

    RUNTIME DESTINATION
    ${CMAKE_INSTALL_PREFIX}/bin
)