cmake_minimum_required(VERSION 3.26)
project(async_task_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(async_task_lib STATIC include/async_task_global.h
        include/async_task_global.cpp
        handle/async_task.cc
        handle/async_task.h
        handle/async_manage.cc
        handle/async_manage.h
        handle/async_task_util.cc
        handle/async_task_util.h)

