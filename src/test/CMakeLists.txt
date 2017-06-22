

find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories(${TEST_SOURCE_DIR}/src
                    ${Boost_INCLUDE_DIRS}
        )

add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable (Test TestDatabaseTask.cpp TestLog.cpp)

target_link_libraries (Test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
