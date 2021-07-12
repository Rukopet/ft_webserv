cmake_minimum_required(VERSION 3.19)
project(ft_webserver)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_webserver main.cpp)


#for google tests
add_subdirectory(googletest)
include_directories(googletest/googletest/include)
target_link_libraries(ft_webserver gtest gtest_main)