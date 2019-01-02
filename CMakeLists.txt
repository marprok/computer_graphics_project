cmake_minimum_required(VERSION 2.8)

project(OpenGL_Project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Bring the headers
include_directories(
    inc/GLEW
    inc/glm
    inc/headers
)

set(SOURCES
    sources/GeometricMesh.cpp
    sources/OBJLoader.cpp
    sources/Renderer.cpp
    sources/ShaderProgram.cpp
    sources/SpotlightNode.cpp
    sources/Tools.cpp
    sources/TextureManager.cpp
    sources/GeometryNode.cpp
)
find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} "main.cpp" ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image GLEW ${OPENGL_LIBRARIES})
