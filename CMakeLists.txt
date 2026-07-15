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
 "src/player.c" "include/player.h" "include/entities.h")

# Your own headers
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

# Copy Assets
add_custom_command(TARGET RPG POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:RPG>/assets"
)