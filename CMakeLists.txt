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


enable_testing()

FOREACH(PatternFamily Creational Structural)
    message("--> Founded patterns family: " ${PatternFamily})

    SET(CUR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${PatternFamily})
    FILE(GLOB children RELATIVE ${CUR_DIR} ${CUR_DIR}/*)
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${CUR_DIR}/${child})
            set(TARGET ${child})
            add_executable(${TARGET}
                ${CUR_DIR}/${child}/${TARGET}.cpp
            )   

            target_link_libraries(${TARGET} PRIVATE Utils gtest_main)

            add_test(${TARGET} ${TARGET})
            SET_TARGET_PROPERTIES (${TARGET} PROPERTIES FOLDER ${PatternFamily})
            message("----> Added " ${PatternFamily} " pattern: " ${TARGET})
        ENDIF()
    ENDFOREACH()
ENDFOREACH()

add_subdirectory(Utils)