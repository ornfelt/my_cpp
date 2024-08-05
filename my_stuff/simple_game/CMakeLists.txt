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
if (WIN32)
	set(BASE_DIR ${CMAKE_SOURCE_DIR})
	set(GLEW_PATH "${BASE_DIR}/glew-2.1.0")
	
	if (NOT SDL2_DIR)
        if (NOT DEFINED ENV{SDL2_DIR})
            message(FATAL_ERROR "SDL2_DIR variable is not set")
        endif()
        set(SDL2_DIR $ENV{SDL2_DIR})
    endif()
	# Very ugly
	if ("${SDL2_DIR}" MATCHES "/cmake$")
        string(REGEX REPLACE "/cmake$" "" SDL2_DIR "${SDL2_DIR}")
    endif()
    
    include_directories(${SDL2_DIR}/include ${GLEW_PATH}/include)
    link_directories(${SDL2_DIR}/lib/x64 ${GLEW_PATH}/lib/Release/x64)
    
    set(SDL2_LIBRARIES SDL2 SDL2main)
    set(GLEW_LIBRARIES glew32 opengl32)
else()
    # Add SDL2
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})

    # Add GLEW
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()

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
	
	# Post-build steps to copy SDL2.dll and glew32.dll to the target build directory
    add_custom_command(TARGET OpenGL_SDL_Movement POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_DIR}/lib/x64/SDL2.dll"
        $<TARGET_FILE_DIR:OpenGL_SDL_Movement>
    )

    add_custom_command(TARGET OpenGL_SDL_Movement POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${GLEW_PATH}/bin/Release/x64/glew32.dll"
        $<TARGET_FILE_DIR:OpenGL_SDL_Movement>
    )
endif()
