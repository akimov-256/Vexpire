cmake_minimum_required(VERSION 3.20)

project(RPG LANGUAGES C)

# C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_WEBP OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_JXL OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TIF OFF CACHE BOOL "" FORCE)

# SDL libraries
add_subdirectory(thirdparty/SDL)
add_subdirectory(thirdparty/SDL_image)
add_subdirectory(thirdparty/SDL_ttf)

# The game
add_executable(RPG
    src/main.c
 "src/player.c" "include/player.h"
 "include/entities.h"
 "src/animation.c" "include/animation.h"
 "src/map.c" "include/map.h"
 "src/camera.c" "include/camera.h")

# Headers
target_include_directories(RPG PRIVATE
    include
)

# Link libraries
target_link_libraries(RPG PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
)

# Copy DLLs
add_custom_command(TARGET RPG POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:RPG>
        $<TARGET_FILE_DIR:RPG>
    COMMAND_EXPAND_LISTS
)

# Copy Directories
add_custom_command(
    OUTPUT "${CMAKE_BINARY_DIR}/assets_stamp.txt"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:RPG>/assets"
    COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_BINARY_DIR}/assets_stamp.txt"
    DEPENDS ${ASSET_FILES}
    COMMENT "Copying asset files"
)

add_custom_command(
    OUTPUT "${CMAKE_BINARY_DIR}/map_stamp.txt"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/map"
        "$<TARGET_FILE_DIR:RPG>/map"
    COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_BINARY_DIR}/map_stamp.txt"
    DEPENDS ${MAP_FILES}
    COMMENT "Copying map files"
)

add_custom_target(CopyAssetFiles ALL DEPENDS "${CMAKE_BINARY_DIR}/assets_stamp.txt")
add_custom_target(CopyMapFiles ALL DEPENDS "${CMAKE_BINARY_DIR}/map_stamp.txt")