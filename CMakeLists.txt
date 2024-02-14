cmake_minimum_required(VERSION 3.12)
project(NBodySimulation)

if (NOT (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL 13))
    message(FATAL_ERROR "GCC version 11 or newer is required.")
	return()
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	message("Build type: DEBUG")
	add_compile_options(-O0 -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	message("Build type: RELEASE")
	add_compile_options(-O3 -march=native -DNDEBUG)
endif()

file(GLOB SOURCES "src/*.cpp")
file(GLOB IMGUI "imgui/*.cpp")
include_directories(include)
include_directories(imgui)

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
link_libraries(glm::glm glfw OpenGL::GL)

add_executable(SimulationGUI "simulation/SimulationGUI.cpp" ${SOURCES} ${IMGUI})
