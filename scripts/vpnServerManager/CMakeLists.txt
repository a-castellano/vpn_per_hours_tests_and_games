project(HTTP_test)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
include(conanbuildinfo.cmake)

conan_basic_setup()
enable_testing()

INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(lib/server_request)

ADD_EXECUTABLE( main src/test.cpp lib/server_request/ServerRequest.cpp )
TARGET_LINK_LIBRARIES( main ${CONAN_LIBS})

ADD_EXECUTABLE( server_request_test tests/server_request_test.cpp lib/server_request/ServerRequest.cpp )
TARGET_LINK_LIBRARIES( server_request_test ${CONAN_LIBS} )

add_test(NAME server_request COMMAND ./bin/server_request_test )
