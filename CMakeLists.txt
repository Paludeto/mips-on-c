cmake_minimum_required(VERSION 3.0)
project(mips-on-c)

# Set C standard (C11)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/instruction_list.c
    src/instruction.c
    src/main.c
    src/parser.c
    src/register.c
)

# Add executable
add_executable(mips_simulator ${SOURCES})