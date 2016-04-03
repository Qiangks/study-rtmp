cmake_minimum_required(VERSION 3.3)
project(rtmp_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp logger.cpp logger.hpp rtmp_server.cpp rtmp_server.hpp error_type.hpp st_thread.cpp st_thread.hpp st_connection.cpp st_connection.hpp utility.cpp utility.hpp srs_kernel_buff.cpp srs_kernel_buff.hpp)
add_executable(rtmp_server ${SOURCE_FILES})