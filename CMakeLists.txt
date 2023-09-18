cmake_minimum_required(VERSION 3.26)
project(async_task_lib)

set(CMAKE_CXX_STANDARD 17)



include_directories(include)
include_directories(handle)


add_library(async_task_lib SHARED include/async_task_global.h
        include/async_task_global.cpp
        handle/async_task.cc
        handle/async_task.h
        handle/async_manage.cc
        handle/async_manage.h
        handle/async_task_util.cc
        handle/async_task_util.h
        test/i_http_task.cc
        test/i_http_task.h)
