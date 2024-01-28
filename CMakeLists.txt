cmake_minimum_required(VERSION 3.12)
project(Simulator)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10)
    message(FATAL_ERROR "GCC version 10 or newer is required.")
	return()
endif()

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
link_libraries(glm::glm glfw OpenGL::GL)

include_directories(include)
file(GLOB SOURCE "src/*.cpp")
add_executable(Simulator ${SOURCE})