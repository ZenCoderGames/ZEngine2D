cmake_minimum_required(VERSION 3.14)
project(ZCoreEngine)

set(CMAKE_CXX_STANDARD 17)

# Tells CMake that the find scripts are inside inside subfolder /cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

# Asks CMake to find the SDL libraries in our system
# Using CONFIG mode with vcpkg
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

# Use local Lua 5.1 build
set(LUA_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/lua")
set(LUA_LIBRARY "${PROJECT_SOURCE_DIR}/lib/lua/lua5.1.lib")
include_directories(${LUA_INCLUDE_DIR})
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

# Set console subsystem for Debug builds to see output
if(MSVC)
    set_target_properties(ZCoreEngine PROPERTIES
        LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
        LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )
endif()

# Asks CMake to link against the libraries during build
# Using vcpkg CMake targets and local Lua
target_link_libraries(ZCoreEngine PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
        $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
        ${LUA_LIBRARY})

# Copy DLL files to output directory after build
add_custom_command(TARGET ZCoreEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:ZCoreEngine>
    $<TARGET_FILE_DIR:ZCoreEngine>
    COMMAND_EXPAND_LISTS
)

# make executable
install(TARGETS ZCoreEngine DESTINATION bin)