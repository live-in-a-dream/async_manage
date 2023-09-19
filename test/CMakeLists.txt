add_subdirectory(googletest)

add_executable(program_test main.cc
        http_test.cc
        http_test.h
)

target_link_libraries(program_test
        gtest_main
        async_task_lib
)

add_test(
        NAME program_test
        COMMAND program_test
)