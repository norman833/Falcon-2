

#find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
#include_directories(${TEST_SOURCE_DIR}/src
#                    ${Boost_INCLUDE_DIRS}
#        )

#add_definitions(-DBOOST_TEST_DYN_LINK)

message(STATUS "This is BINARY dir " ${CMAKE_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${CMAKE_SOURCE_DIR})
set(SOURCE_FILES TestMain.cpp TestDatabaseTask.cpp TestLog.cpp)

add_executable(TestRunner ${SOURCE_FILES})

#target_link_libraries (Test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
