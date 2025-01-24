cmake_minimum_required(VERSION 3.10)
project(First)

set(CMAKE_CXX_STANDARD 17)

# Find and link required libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add the executable and specify the source file path
add_executable(OpenGLProject ${CMAKE_SOURCE_DIR}/main.cpp)

# Link the libraries
target_link_libraries(OpenGLProject OpenGL::GL glfw GLEW::GLEW)
