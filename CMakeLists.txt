#CMakeLists.txt 

cmake_minimum_required(VERSION 2.6)

project(kill-gosts)
include_directories("src/")
include_directories("/usr/include/irrlicht")

file(
GLOB_RECURSE
source_files
src/*.[cht]pp
)


add_executable(kill-gosts ${source_files})

SET(CMAKE_BUILD_TYPE Debug)
ADD_DEFINITIONS( -O2 -Wall -Wextra -std=c++11 -Wno-comment -Wno-unused-parameter -Wno-unused-function )

TARGET_LINK_LIBRARIES(kill-gosts -lIrrlicht)

