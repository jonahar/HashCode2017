cmake_minimum_required(VERSION 3.6)
project(HashCode2017)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wvla -Wextra")

set(SOURCE_FILES src/Organizer.cpp src/Video.cpp src/Video.h src/Cache.cpp src/Cache.h src/Endpoint.cpp src/Endpoint.h src/Network.cpp src/Network.h)
add_executable(HashCode2017 ${SOURCE_FILES})