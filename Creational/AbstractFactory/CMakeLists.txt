
set(TARGET AbstractFactory)

add_executable(${TARGET}
    AbstractFactory.cpp
)   

target_link_libraries(${TARGET} PRIVATE gtest_main)