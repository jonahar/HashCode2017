cmake_minimum_required(VERSION 3.6)
project(HashCode2017)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES main.cpp Video.cpp Video.h Cache.cpp Cache.h Endpoint.cpp Endpoint.h)
add_executable(HashCode2017 ${SOURCE_FILES})