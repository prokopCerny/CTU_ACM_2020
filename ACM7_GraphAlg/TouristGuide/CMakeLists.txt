cmake_minimum_required(VERSION 3.10)
project(TouristGuide)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DMY_DEBUG")

add_executable(TouristGuide main.cpp)