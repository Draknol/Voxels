cmake_minimum_required(VERSION 3.15)
project(voxels VERSION 0.1.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(unofficial-inih CONFIG REQUIRED)

file(GLOB_RECURSE SRC src/*.cpp src/*.c)

add_executable(voxels ${SRC})

target_include_directories(voxels PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(voxels PRIVATE OpenGL::GL glfw GLEW::GLEW unofficial::inih::inireader)