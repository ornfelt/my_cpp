cmake_minimum_required(VERSION 3.10)
project(OpenGL_SDL_Movement)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the packages
find_package(OpenGL REQUIRED)

# Add SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# Source files
set(SOURCES main.cpp)

# Executable
add_executable(OpenGL_SDL_Movement ${SOURCES})

# Link libraries
target_link_libraries(OpenGL_SDL_Movement ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES})

# Platform-specific settings
if (WIN32)
    # Additional settings for Windows
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()
