
set(TARGET AbstractFactory)

add_executable(${TARGET}
    AbstractFactory.cpp
)   

target_link_libraries(${TARGET} PRIVATE Utils gtest_main)

add_test(AbstractFactory AbstractFactory)