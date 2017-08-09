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
include_directories("src/marketdata")
include_directories("src/gateway")

#gw included
include_directories("src/gateway/cme")



# Add sub dirs
add_subdirectory("src/database")
add_subdirectory("src/base")
add_subdirectory("src/network")
add_subdirectory("src/marketdata")
add_subdirectory("src/marketaccess")
add_subdirectory("src/gateway")

#gw sub dirs
add_subdirectory("src/gateway/cme")

#test subdir
add_subdirectory("src/test")

set(SOURCE_FILES src/main.cpp)

add_executable(Falcon ${SOURCE_FILES})

find_package(Boost 1.64 REQUIRED COMPONENTS system)
find_package(Poco REQUIRED Foundation Util Net)
find_library(FIX8_LIB fix8)
find_library(MySQLConn_LIB mysqlcppconn)


message(STATUS "Boost libs are " ${Boost_LIBRARIES})
message(STATUS "FIX8 lib is " ${FIX8_LIB})
message(STATUS "POCO lib is " ${Poco_LIBRARIES})
message(STATUS "MySQL Connector lib is " ${MySQLConn_LIB})


target_link_libraries(Falcon database base network marketdata marketaccess cme ${Poco_LIBRARIES} ${FIX8_LIB} ${MySQLConn_LIB} ${Boost_LIBRARIES} )

# Testing
enable_testing()

add_test(NAME FalconTest COMMAND TestRunner)