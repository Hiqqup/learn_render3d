cmake_minimum_required(VERSION 3.28)
project(render_3d)

set(CMAKE_CXX_STANDARD 20)



set(EXE_FILE render3d)
add_executable(${EXE_FILE} src/main.cpp
        src/Shader.cpp
        src/Shader.h
        src/oldMeshAndEntityClasses/Mesh2D.cpp
        src/oldMeshAndEntityClasses/Mesh2D.h
        src/Window.cpp
        src/Window.h
        src/Assets.h
        src/oldMeshAndEntityClasses/Mesh3dFromModel.cpp
        src/oldMeshAndEntityClasses/Mesh3dFromModel.h
        src/oldMeshAndEntityClasses/Entity3dFromModel.cpp
        src/oldMeshAndEntityClasses/Entity3dFromModel.h
        src/oldMeshAndEntityClasses/CubeWithNormals.cpp
        src/oldMeshAndEntityClasses/CubeWithNormals.h
        )

include(cmake/Libraries.cmake)

target_compile_definitions(${EXE_FILE} PRIVATE ASSET_ROOT=./assets/)

# copy assets to output directory before build
add_custom_command(TARGET ${EXE_FILE} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${EXE_FILE}>/assets)
