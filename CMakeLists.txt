cmake_minimum_required(VERSION 3.7)
project(Falcon)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DBOOST_LOG_DYN_LINK)
find_package(Boost 1.64.0 COMPONENTS log REQUIRED)
if(Boost_FOUND)
    #include_directories( ${Boost_INCLUDE_DIRS} )
    link_libraries(${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
else(Boost_FOUND)
    message(FATAL_ERROR "Cannot link Boost libs.")
endif(Boost_FOUND)

set(SOURCE_FILES src/main.cpp)
add_executable(Falcon ${SOURCE_FILES})
