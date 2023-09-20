cmake_minimum_required(VERSION 3.25)
project(Server)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.82.0 COMPONENTS system REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} include)

add_library(tcp_server src/tcp_server.cpp)
add_library(tcp_connection src/tcp_connection.cpp)

add_executable(server_app src/main.cpp)
target_link_libraries(server_app tcp_server tcp_connection ${Boost_LIBRARIES})