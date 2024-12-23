# mips-on-c

# Project Build Instructions

This guide explains how to build and run the project using CMake and Make.

## Prerequisites

Make sure the following tools are installed on your system:

1. **CMake**: To generate build files.
2. **Make**: To compile and link the project.
3. **C Compiler**: GCC or equivalent C compiler.

To check if these tools are installed, run:
```bash
cmake --version
gcc --version
make --version
```
If any of these commands fail, install the missing tools.

### Installing Dependencies
- **Ubuntu/Debian**:
  ```bash
  sudo apt update
  sudo apt install -y build-essential cmake
  ```
- **Fedora**:
  ```bash
  sudo dnf install -y gcc gcc-c++ make cmake
  ```
- **Arch Linux**:
  ```bash
  sudo pacman -Syu base-devel cmake
  ```

## Build and Run Instructions

1. **Clone the repository** (if you haven’t already):
   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```

2. **Create a build directory**:
   ```bash
   mkdir build && cd build
   ```

3. **Generate the build system using CMake**:
   ```bash
   cmake ..
   ```
   This will generate the necessary Makefiles in the `build` directory.

4. **Compile the project using Make**:
   ```bash
   make
   ```

5. **Run the program**:
   ```bash
   ./mips_simulator
   ```

## Clean Build

To clean up all generated files and rebuild the project from scratch:

1. **Remove the `build` directory**:
   ```bash
   rm -rf build
   ```

2. **Repeat the build process** starting from step 2.

---