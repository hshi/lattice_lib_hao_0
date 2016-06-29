cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(latticehao)

#For find module path
set(CMAKE_MODULE_PATH "${MODULE_EXTRA_PATH}" ${CMAKE_MODULE_PATH})

#For definitions
add_definitions(${COMPILER_EXTRA_DEF})

#For c++ flag
if(CMAKE_CXX_FLAGS STREQUAL "")
   set(CMAKE_CXX_FLAGS "-Wall -O3 -std=c++11")
endif()

include_directories(inc)

add_subdirectory(inc)

add_subdirectory(src)

add_subdirectory(test)
