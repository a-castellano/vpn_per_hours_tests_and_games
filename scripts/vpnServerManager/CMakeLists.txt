project(HTTP_test)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
include(conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(lib/server_request)
ADD_EXECUTABLE(test src/test.cpp lib/server_request/ServerRequest.cpp)
TARGET_LINK_LIBRARIES(test ${CONAN_LIBS})
