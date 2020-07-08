cmake_minimum_required(VERSION 3.10)

# set the project name
project(Examples_of_patterns LANGUAGES CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

add_subdirectory(googletest EXCLUDE_FROM_ALL)
SET_TARGET_PROPERTIES (gtest PROPERTIES FOLDER gtest/)
SET_TARGET_PROPERTIES (gtest_main PROPERTIES FOLDER gtest/)
add_subdirectory(Creational)
add_subdirectory(Utils)