cmake_minimum_required(VERSION 3.9)

project(leetCode)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(INCLUDE_PATH ./)

include_directories("${INCLUDE_PATH}")

add_executable(leetCode 0009.cpp)

target_link_libraries(leetCode gtest gmock)
