cmake_minimum_required(VERSION 3.10)
project(coro_test)

set(CORO_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../coro_lib)
link_directories(${CORO_LIB_DIR}/build)

add_executable(coro-test test.c)

target_include_directories(coro-test PUBLIC ${CORO_LIB_DIR})
target_link_libraries(coro-test coro_lib)