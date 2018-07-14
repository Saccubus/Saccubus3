cmake_minimum_required(VERSION 3.9)
project (Saccubus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#Main src directory
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SRCS ${SRC_DIR}/*.c ${SRC_DIR}/*.cpp)

find_package(PkgConfig)

# executable
pkg_check_modules(SDL2 REQUIRED sdl2)
message(Building SDL2 version)
include_directories(${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})

# binary
add_library(sacc SHARED ${SRCS})
target_link_libraries(sacc ${SDL2_LIBRARIES})
