cmake_minimum_required(VERSION 3.10)
project(coro_lib_test)

add_executable(coro_test test.c)

add_subdirectory(coro_lib)

target_include_directories(coro_test PRIVATE coro_lib)
target_link_libraries(coro_test coro_lib)