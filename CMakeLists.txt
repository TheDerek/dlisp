cmake_minimum_required(VERSION 3.5)
project(dlisp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Include base code + folders
file(GLOB_RECURSE SOURCE_FILES "*.h" "*.cpp")
add_executable(dlisp ${SOURCE_FILES})