cmake_minimum_required(VERSION 3.10)

project(RPG LANGUAGES C)

# Create the executable
add_executable(RPG
    src/main.c
)

# Use the C17 standard
set_property(TARGET RPG PROPERTY C_STANDARD 17)
set_property(TARGET RPG PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET RPG PROPERTY C_EXTENSIONS OFF)