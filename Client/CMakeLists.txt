cmake_minimum_required(VERSION 3.25)
project(Client)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.82.0 COMPONENTS system REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} include)

add_library(tcp_client src/tcp_client.cpp)

add_executable(client_app src/main.cpp)
target_link_libraries(client_app tcp_client ${Boost_LIBRARIES})