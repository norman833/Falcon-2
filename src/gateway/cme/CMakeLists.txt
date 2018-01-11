find_library(QuickFIX_LIB quickfix)
find_library(PThread_LIB pthread)
find_library(XML2_LIB xml2)
find_library(ZDev_LIB z)

message(STATUS "QuickFix lib is " ${QuickFIX_LIB})
message(STATUS "XML2 lib is " ${XML2_LIB})
message(STATUS "PThread lib is " ${PThread_LIB})
message(STATUS "ZDev lib is " ${ZDev_LIB})

add_library(Falcon SHARED CMEGateWay.cpp CMEApplication.cpp CMEOrderInterface.h)

target_link_libraries(Falcon ${QuickFIX_LIB} ${XML2_LIB} ${PThread_LIB} ${ZDev_LIB})