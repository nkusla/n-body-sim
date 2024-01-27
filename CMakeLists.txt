cmake_minimum_required(VERSION 3.12)
project(NBodySim)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10)
    message(FATAL_ERROR "GCC version 10 or newer is required.")
	return()
endif()

add_executable(NBodySim src/main.cpp)