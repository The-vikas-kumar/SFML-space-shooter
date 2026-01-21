cmake_minimum_required(VERSION 3.20)

project(SpaceShooter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------
# Paths (workspace-based)
# -------------------------------
set(PROJECT_ROOT ${CMAKE_SOURCE_DIR})

set(SRC_DIR ${PROJECT_ROOT}/src)
set(INCLUDE_DIR ${PROJECT_ROOT}/include)
set(ASSETS_DIR ${PROJECT_ROOT}/assets)

set(SFML_ROOT ${PROJECT_ROOT}/external/sfml)
set(SFML_INCLUDE_DIR ${SFML_ROOT}/include)
set(SFML_LIB_DIR ${SFML_ROOT}/lib)

set(SFML_STATIC_LIBRARIES TRUE)
add_definitions(-DSFML_STATIC)

# -------------------------------
# Collect source files
# -------------------------------
file(GLOB_RECURSE SOURCES
    ${SRC_DIR}/*.cpp
)

# -------------------------------
# Create executable
# -------------------------------
add_executable(SpaceShooter ${SOURCES})

# -------------------------------
# Include directories
# -------------------------------
target_include_directories(SpaceShooter PRIVATE
    ${INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
)

# -------------------------------
# Link SFML libraries
# -------------------------------
target_link_directories(SpaceShooter PRIVATE
    ${SFML_LIB_DIR}
)

target_link_libraries(SpaceShooter
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
)

file(COPY ${CMAKE_SOURCE_DIR}/assets
    DESTINATION ${CMAKE_BINARY_DIR}
)