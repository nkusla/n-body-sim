cmake_minimum_required(VERSION 3.12)
project(NBodySimulator)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11)
    message(FATAL_ERROR "GCC version 10 or newer is required.")
	return()
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(DEBUG "Building in RELEASE mode" ON)

if (DEBUG)
	message("Building in DEBUG mode")
	add_compile_options(-g)
else()
	message("Building in RELEASE mode")
	add_compile_options(-03 -DNDEBUG)
endif()

file(GLOB SOURCES "src/*.cpp")
include_directories(include)

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
link_libraries(glm::glm glfw OpenGL::GL)

add_executable(SimulatorGUI "simulator/SimulatorGUI.cpp" ${SOURCES})
add_executable(SimulatorNoGUI "simulator/SimulatorNoGUI.cpp" ${SOURCES})