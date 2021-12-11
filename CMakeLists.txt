cmake_minimum_required(VERSION 3.19)
project(ft_webserver)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")
set(SOURCE_FILES main.cpp other_example_for_tests.cpp Server/Server.cpp Logger/Logger.cpp Logger/Logger.hpp Parser/Parser.cpp Parser/ServerConfig.cpp Parser/Config.cpp Parser/RouteConfig.cpp Client/SocketClient.cpp Client/SocketClient.hpp Client/Request.cpp Client/Request.hpp Client/SocketBase.hpp Client/RequestBase.hpp Client/Request.cpp Client/Request.hpp Server/ServerUtils.cpp Server/ServerUtils.hpp Server/ConnectionsClients.cpp Server/ConnectionsClients.hpp Server/ConnectionsBase.hpp Server/ConnectionsMainSockets.cpp Server/ConnectionsMainSockets.hpp)
set(SOURCES_FOR_TEST Client/Request.cpp Client/SocketClient.cpp Server/ServerUtils.cpp Server/ServerUtils.hpp)
set(TESTS_SOURCE UnitTests/ClientRequestFixture.cpp Server/ServerUtils.cpp Server/ServerUtils.hpp)

# this executable for simple RUN, and DEBUG
add_executable(ft_webserver ${SOURCE_FILES})

# this executable for google tests dont need adding main to this. Also u can RUN with coverage
add_executable(All_tests ${SOURCES_FOR_TEST} ${TESTS_SOURCE})
add_executable(shit main_for_check_nonblock.cpp)
add_executable(parser parser/Config.cpp parser/Parser.cpp parser/RouteConfig.cpp parser/IParser.hpp parser/ServerConfig.cpp)
add_executable(test_behavior parser/Config.cpp parser/Parser.cpp parser/RouteConfig.cpp parser/IParser.hpp parser/ServerConfig.cpp)

#for google tests
add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)
target_link_libraries(All_tests gtest gtest_main gmock gmock_main)