cmake_minimum_required(VERSION 3.27)
project(code)
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD 14)
#
#set(CMAKE_CXX_STANDARD 98)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(code
#        thread/MyThread.cpp
#        lrvalue/testLrValue.cpp
#        newFeature/OriginalLiteral.cpp
#        newFeature/nullptr.cpp
#        newFeature/constexpr.cpp
#        newFeature/auto.cpp
#        newFeature/decltype.cpp
#        newFeature/final.cpp
#        newFeature/override.cpp
#        newFeature/template.cpp
#        newFeature/using.cpp
        newFeature/wrapandextend.cpp
        #        Hello.cpp
#        MyMap.cpp
#        MyParam.cpp
#        MyVector.cpp
)

target_link_libraries(code PRIVATE pthread)

