cmake_minimum_required(VERSION 3.14)
project(ZCoreEngine)

set(CMAKE_CXX_STANDARD 14)

# Tells CMake that the find scripts are inside inside subfolder /cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

# Asks CMake to find the SDL libraries in our system
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Lua51 REQUIRED)

# Asks CMake to include the library folders during build
include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR})

# Include lua
include_directories(/usr/local/include ${LUA_INCLUDE_DIR})
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/glm)

# Recursively add files
file (GLOB_RECURSE SRC_CPP_FILES src/*.cpp )
file (GLOB_RECURSE SRC_H_FILES src/*.h)
set (SRC_FILES ${SRC_CPP_FILES} ${SRC_H_FILES})

file (GLOB_RECURSE LIB_CPP_FILES lib/lua/*.cpp )
file (GLOB_RECURSE LIB_H_FILES lib/lua/*.h)
file(GLOB_RECURSE LIB_JSON_FILES lib/json/*.hpp)
set (LIB_FILES ${LIB_CPP_FILES} ${LIB_H_FILES} ${LIB_JSON_FILES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Adds the files that are part of the project
add_executable(ZCoreEngine
        ${SRC_FILES}
        ${LIB_FILES})

# Asks CMake to link against the libraries during build
target_link_libraries(ZCoreEngine
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${LUA_LIBRARIES})

# make executable
install(TARGETS ZCoreEngine DESTINATION bin)