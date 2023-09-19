cmake_minimum_required(VERSION 3.26)
project(async_task)

set(CMAKE_CXX_STANDARD 17)

include_directories(async_task_lib)

add_subdirectory(async_task_lib)

enable_testing()
add_subdirectory(test)

