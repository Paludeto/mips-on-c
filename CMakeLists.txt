cmake_minimum_required(VERSION 3.5)
project(mips-on-c)

# Set C standard (C23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/instruction_list.c
    src/label_list.c
    src/executors.c
    src/main.c
    src/parser.c
    src/register.c
)

# Add executable
add_executable(mips_simulator ${SOURCES})