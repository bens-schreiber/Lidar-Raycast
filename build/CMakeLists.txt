cmake_minimum_required(VERSION 3.10)
project(3d-bvh-tree)

set(CMAKE_C_STANDARD 99)

add_executable(game ../src/main.c ../src/bvh/bvh.c ../src/camera/camera.c ../src/renderable/renderable.c ../src/scene/scene.c)

include_directories(../lib/raylib/src)

find_library(COCOA_LIBRARY Cocoa)
find_library(GLUT_LIBRARY GLUT)
find_library(OPENGL_LIBRARY OpenGL)
find_library(IOKIT_LIBRARY IOKit)
find_library(COREVIDEO_LIBRARY CoreVideo)
find_library(RAYLIB_LIBRARY NAMES raylib PATHS ../lib/raylib)

target_link_libraries(game ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY} ${RAYLIB_LIBRARY})