FILE(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
FOREACH(child ${children})
    IF(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child})
        set(TARGET ${child})
        add_executable(${TARGET}
            ${child}/${TARGET}.cpp
        )   

        target_link_libraries(${TARGET} PRIVATE Utils gtest_main)

        add_test(${TARGET} ${TARGET})
        message("-----> Added pattern: " ${TARGET})
    ENDIF()
ENDFOREACH()
