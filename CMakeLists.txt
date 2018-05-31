cmake_minimum_required(VERSION 3.10)
project(EX8)

set(CMAKE_CXX_STANDARD 11)

add_executable(EX8 main.cpp Board.h Pair.cpp Pair.h IllegalCharException.cpp IllegalCharException.h IllegalCoordinateException.cpp IllegalCoordinateException.h Board.cpp)