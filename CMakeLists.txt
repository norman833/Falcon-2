cmake_minimum_required(VERSION 3.7)
project(FalconServer)
#set(CMAKE_BUILD_TYPE Release)

#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-fexceptions")

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/include)

message(STATUS "This is BINARY dir " ${CMAKE_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${CMAKE_SOURCE_DIR})
message(STATUS "This is LIBRARY_OUTPUT_PATH " ${LIBRARY_OUTPUT_PATH})
message(STATUS "This is CMAKE_INSTALL_PREFIX " ${CMAKE_INSTALL_PREFIX})

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
        /lib
        /usr/lib
        /usr/lib64
        /usr/local/lib
        /usr/local/lib64
        /usr/lib/x86_64-linux-gnu)
message(STATUS "This is CMAKE_LIBRARY_PATH " ${CMAKE_LIBRARY_PATH})

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

set(SOURCE_FILES)

add_library(Falcon SHARED ${SOURCE_FILES})
add_executable(FalconServer src/main.cpp)

#find_package(Boost 1.64 REQUIRED COMPONENTS system)
#find_library(MySQLConn_LIB mysqlcppconn)

find_library(QuickFIX_LIB quickfix)
find_library(PThread_LIB pthread)
find_library(XML2_LIB xml2)
find_library(ZDev_LIB z)

#message(STATUS "Boost libs are " ${Boost_LIBRARIES})

message(STATUS "QuickFix lib is " ${QuickFIX_LIB})
message(STATUS "XML2 lib is " ${XML2_LIB})
#message(STATUS "MySQL Connector lib is " ${MySQLConn_LIB})
message(STATUS "PThread lib is " ${PThread_LIB})
message(STATUS "ZDev lib is " ${ZDev_LIB})


#target_link_libraries(Falcon database base network marketdata marketaccess cme ${QuickFIX_LIB} ${XML2_LIB} ${PThread_LIB} ${ZDev_LIB} )

target_link_libraries(Falcon base cme ${QuickFIX_LIB} ${XML2_LIB} ${PThread_LIB} ${ZDev_LIB} )

target_link_libraries(FalconServer Falcon )

install(FILES src/base/Logger.h
        src/gateway/cme/CMEGateWay.h
        src/gateway/cme/CMEApplication.h
        src/gateway/cme/CMEOrderInterface.h

        DESTINATION ${CMAKE_INSTALL_PREFIX})
# Testing
enable_testing()

add_test(NAME FalconTest COMMAND TestRunner)