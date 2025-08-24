cmake_minimum_required(VERSION 3.16)
project(SpaceShooter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Where SFML is located in your repo/workspace
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/sfml")

# Output folder
set(BUILD_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_OUTPUT_DIR}")

# Compiler flags for static SFML and debug/release
add_compile_definitions(SFML_STATIC)        # equivalent to -DSFML_STATIC

# Source files
file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.cxx")
add_executable(game ${SRC_FILES})

# Include and lib directories
target_include_directories(game PRIVATE "${CMAKE_SOURCE_DIR}/include" "${SFML_ROOT}/include")
link_directories("${SFML_ROOT}/lib")

# Link libraries - IMPORTANT: module libs come first, deps after.
# Adjust names if your libs include -d suffix for debug builds.
target_link_libraries(game PRIVATE
    sfml-graphics-s
    sfml-window-s
    sfml-audio-s
    sfml-system-s

    # system / backend libs
    opengl32
    freetype
    winmm
    gdi32

    # audio dependencies (SFML expects these)
    flac
    vorbisenc
    vorbisfile
    vorbis
    ogg
    openal32
)

# Post-build: copy DLLs from sfml/bin into build folder (if any)
if(EXISTS "${SFML_ROOT}/bin")
    file(GLOB SFML_DLLS "${SFML_ROOT}/bin/*.dll")
    foreach(_dll ${SFML_DLLS})
        add_custom_command(TARGET game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${_dll}" "$<TARGET_FILE_DIR:game>"
        )
    endforeach()
endif()

# Optional: set different libraries for Debug if you have -s-d variants
# Example:
# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#   target_link_libraries(game PRIVATE sfml-graphics-s-d ...)
# endif()
