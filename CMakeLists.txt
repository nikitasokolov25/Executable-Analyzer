cmake_minimum_required(VERSION 3.0)

project(ExecutableAnalyzer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

file(GLOB FOXSOURCES "src/*.cpp")
file(GLOB IMGUISOURCES "libs/imgui/imgui*.cpp")
set(FOXSOURCES "${FOXSOURCES};${PROJECT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_opengl2.cpp")
set(FOXSOURCES "${FOXSOURCES};${PROJECT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_glfw.cpp")
set(FOXSOURCES "${FOXSOURCES};${IMGUISOURCES}")

message("FOXSOURCES contains ${FOXSOURCES}")

include_directories("${PROJECT_SOURCE_DIR}/libs/imgui")
include_directories("${PROJECT_SOURCE_DIR}/libs/glfw/include")
include_directories("${PROJECT_SOURCE_DIR}/libs/imgui/backends")

#dont build GLFW  docs tests exmaples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("libs/glfw/")

#look for opengl
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} ${FOXSOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} glfw)

if(WIN32)
  target_link_libraries(${CMAKE_PROJECT_NAME} opengl32.lib gdi32.lib shell32.lib)
endif(WIN32)

if(UNIX)
  target_link_libraries(${CMAKE_PROJECT_NAME} GL)
endif(UNIX)

#foxlib opengl32.lib gdi32.lib shell32.lib
