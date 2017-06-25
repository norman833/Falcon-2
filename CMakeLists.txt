cmake_minimum_required(VERSION 3.7)
project(Falcon)

set(CMAKE_CXX_STANDARD 11)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

message(STATUS "This is BINARY dir " ${CMAKE_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${CMAKE_SOURCE_DIR})

add_definitions(-DLOGGING_LEVEL_1)

# The following folder will be included
include_directories("src/database")
include_directories("src/base")
include_directories("src/network")

# Add sub dirs
add_subdirectory("src/database")
add_subdirectory("src/base")
add_subdirectory("src/network")

add_subdirectory("src/test")

set(SOURCE_FILES src/main.cpp)

add_executable(Falcon ${SOURCE_FILES})

target_link_libraries (Falcon database base)

# Testing
enable_testing()

add_test(NAME FalconTest COMMAND TestRunner)