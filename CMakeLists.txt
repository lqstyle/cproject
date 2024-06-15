cmake_minimum_required(VERSION 3.27)
project(code)

set(CMAKE_CXX_STANDARD 11)

add_executable(code
#        thread/MyThread.cpp
        lrvalue/testLrValue.cpp
        newFeature/OriginalLiteral.cpp
        newFeature/nullptr.cpp
        #        Hello.cpp
#        MyMap.cpp
#        MyParam.cpp
#        MyVector.cpp
)

target_link_libraries(code PRIVATE pthread)

