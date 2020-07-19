get_filename_component(PatternFamily ${CMAKE_CURRENT_LIST_DIR} NAME)
message("--> Founded patterns family: " ${PatternFamily})

FILE(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
FOREACH(child ${children})
    IF(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child})
        set(TARGET ${child})
        add_executable(${TARGET}
            ${child}/${TARGET}.cpp
        )   

        target_link_libraries(${TARGET} PRIVATE Utils gtest_main)

        add_test(${TARGET} ${TARGET})
        SET_TARGET_PROPERTIES (${TARGET} PROPERTIES FOLDER ${PatternFamily})
        message("----> Added " ${PatternFamily} " pattern: " ${TARGET})
    ENDIF()
ENDFOREACH()
