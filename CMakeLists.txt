cmake_minimum_required(VERSION 3.9)

project(leetcode)

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "current platform: Linux ")
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "current platform: Windows")
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    message(STATUS "current platform: Mac os x")
    SET(CMAKE_C_COMPILER /opt/homebrew/opt/llvm/bin/clang)
    SET(CMAKE_CXX_COMPILER /opt/homebrew/opt/llvm/bin/clang++)
    SET(INC_PATH_EXTRA "/opt/homebrew/opt/llvm/include" "/opt/homebrew/Cellar/googletest/1.14.0/include")
    SET(LINK_PATH_EXTRA "/opt/homebrew/opt/llvm/lib" "/opt/homebrew/Cellar/googletest/1.14.0/lib")
ELSE()
    message(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

link_directories(
    ${LINK_PATH_EXTRA}
)

include_directories(
    ${INC_PATH_EXTRA}
    ./
)

add_executable(leetcode 0019.cpp)

target_link_libraries(leetcode gtest gmock)
