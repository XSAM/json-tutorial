cmake_minimum_required (VERSION 3.5)
# THIS HAS TO COME BEFORE THE PROJECT LINE
# set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")

project (leptjson_test C)

# if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
#     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
# endif()

add_library(leptjson leptjson.c)

add_executable(leptjson_test test.c)
target_link_libraries(leptjson_test leptjson)
