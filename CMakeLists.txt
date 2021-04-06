cmake_minimum_required(VERSION 2.8)
project(euchre)

include_directories(.)
include(gtest.cmake)

find_package(Threads)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -pthread")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

add_executable(euchre src/Card.cpp src/Player.cpp src/Game.cpp src/main.cpp)
add_executable(euchre-test test/test.cpp src/Card.cpp src/Player.cpp src/Game.cpp)
target_link_libraries(euchre-test googletest ${CMAKE_THREAD_LIBS_INIT})
