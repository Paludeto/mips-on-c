cmake_minimum_required(VERSION 3.5)
project(mips-on-c)

# Set C standard (C23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/instructions.c
    src/label.c
    src/executors.c
    src/memory.c
    src/main.c
    src/parser.c
    src/register.c
    src/encoder.c
    src/validator.c
    src/menu.c
)

# Add executable
add_executable(mips_simulator ${SOURCES})

add_compile_options(-O3, -WAll)