cmake_minimum_required(VERSION 3.27)
project(code)
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD 14)
#
#set(CMAKE_CXX_STANDARD 98)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

add_executable(code
#        thread/MyThread.cpp
#        lrvalue/testLrValue.cpp
#        newFeature/OriginalLiteral01.cpp
#        newFeature/nullptr02.cpp
        newFeature/cancallbind10.cpp
        #        newFeature/constexpr03.cpp
#        newFeature/auto041.cpp
#        newFeature/decltype042.cpp
#        newFeature/final.cpp
#        newFeature/override.cpp
#        newFeature/template07.cpp
#        newFeature/using06.cpp
#        newFeature/wrapandextend.cpp
#        newFeature/lrvalue09.cpp
        #        Hello.cpp
#        MyMap.cpp
#        MyParam.cpp
#        MyVector.cpp
)

target_link_libraries(code PRIVATE pthread)

