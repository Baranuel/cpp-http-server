# CMakeLists.txt - Build configuration file for CMake
# CMake is a build system that generates platform-specific build files

# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
# This creates variables like PROJECT_NAME that can be used later
project(cpp-server VERSION 1.0)

# Set the C++ standard to C++17
# This ensures we use modern C++ features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Generate compile_commands.json for better IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add compiler flags for better debugging and warnings
# -Wall: Enable all common warnings
# -Wextra: Enable extra warnings
# -g: Include debugging information
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Debug-specific flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
# Release-specific flags
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

include_directories(include)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# Create an executable target
# This tells CMake to create an executable named "server" from main.cpp
add_executable(server ${SOURCE_FILES})

# Optional: If you need to link additional libraries later
# For example, if you need pthread for threading:
# find_package(Threads REQUIRED)
# target_link_libraries(server Threads::Threads)
