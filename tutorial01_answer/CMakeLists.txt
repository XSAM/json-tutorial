cmake_minimum_required (VERSION 2.6)
project (leptjson_test C)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

add_library(leptjson01_answer leptjson.c)
add_executable(leptjson_answer_test test.c)
target_link_libraries(leptjson_answer_test leptjson01_answer)
