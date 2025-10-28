cmake_minimum_required(VERSION 3.28)
project(render_3d)

set(CMAKE_CXX_STANDARD 20)


include(FetchContent)

set(EXE_FILE render3d)
add_executable(${EXE_FILE} src/main.cpp
        src/Shader.cpp
        src/Shader.h
        src/Mesh.cpp
        src/Mesh.h
        src/Window.cpp
        src/Window.h
        src/Assets.h)

include(cmake/Libraries.cmake)

target_compile_definitions(${EXE_FILE} PRIVATE ASSET_ROOT=./assets/)

# copy assets to output directory before build
add_custom_command(TARGET ${EXE_FILE} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${EXE_FILE}>/assets)
