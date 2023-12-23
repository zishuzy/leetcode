cmake_minimum_required(VERSION 3.9)

project(leetcode)

SET(CMAKE_C_COMPILER /opt/homebrew/opt/llvm/bin/clang)
SET(CMAKE_CXX_COMPILER /opt/homebrew/opt/llvm/bin/clang++)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

link_directories(
    /opt/homebrew/opt/llvm/lib
    /opt/homebrew/Cellar/googletest/1.14.0/lib
)

include_directories(
    /opt/homebrew/opt/llvm/include
    /opt/homebrew/Cellar/googletest/1.14.0/include
    ./
)

add_executable(leetcode 0018.cpp)

target_link_libraries(leetcode gtest gmock)
