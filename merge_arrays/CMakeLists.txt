cmake_minimum_required(VERSION 3.10)
project(merge-sort)

set(CORO_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../coro_lib)
link_directories(${CORO_LIB_DIR}/build)

add_executable(merge-sort merge-sort.c)

target_include_directories(merge-sort PUBLIC ${CORO_LIB_DIR})
target_link_libraries(merge-sort coro_lib)