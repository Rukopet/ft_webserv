cmake_minimum_required(VERSION 3.19)
project(ft_webserver)

set(CMAKE_CXX_STANDARD 98)

# this executable for simple RUN, and DEBUG
add_executable(ft_webserver main.cpp other_example_for_tests.cpp Server/Server.cpp Logger/Logger.cpp Logger/Logger.hpp)

# this executable for google tests dont need adding main to this. Also u can RUN with coverage
add_executable(All_tests UnitTests/Example_test.cpp other_example_for_tests.cpp UnitTests/ExeptionTest.cpp)
add_executable(shit main_for_check_nonblock.cpp)
add_executable(parser parser/Config.cpp parser/Parser.cpp parser/RouteConfig.cpp parser/IParser.hpp parser/ServerConfig.cpp)
add_executable(test_behavior parser/Config.cpp parser/Parser.cpp parser/RouteConfig.cpp parser/IParser.hpp parser/ServerConfig.cpp test_behavior.cpp)

#for google tests
add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)
target_link_libraries(ft_webserver gtest gtest_main)
target_link_libraries(All_tests gtest gtest_main gmock gmock_main)