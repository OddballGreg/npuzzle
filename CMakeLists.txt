cmake_minimum_required(VERSION 3.6)
project(npuzzelc__)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g3 -std=c++11")

set(SOURCE_FILES main.cpp npuzzle.h Node.cpp Node.h suportFunctions.cpp suportFunctions.h huristics.cpp parse.cpp solve.cpp)
add_executable(npuzzelc__ ${SOURCE_FILES})