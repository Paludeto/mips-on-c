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

# mips-on-c

# Instruções de Build do Projeto

Este guia explica como compilar e executar o projeto utilizando CMake e Make.

## Pré-requisitos

Certifique-se de que as seguintes ferramentas estejam instaladas em seu sistema:

1. **CMake**: Para gerar os arquivos de build.
2. **Make**: Para compilar e vincular o projeto.
3. **Compilador C**: GCC ou outro compilador C equivalente.

Para verificar se estas ferramentas estão instaladas, execute:
```bash
cmake --version
gcc --version
make --version
```
Se algum destes comandos falhar, instale a ferramenta que estiver faltando.

### Instalando Dependências
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

## Instruções de Build e Execução

1. **Clone o repositório** (caso ainda não o tenha feito):
   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```

2. **Crie um diretório de build**:
   ```bash
   mkdir build && cd build
   ```

3. **Gere o sistema de build usando CMake**:
   ```bash
   cmake ..
   ```
   Isso gerará os Makefiles necessários no diretório `build`.

4. **Compile o projeto usando Make**:
   ```bash
   make
   ```

5. **Execute o programa**:
   ```bash
   ./mips_simulator
   ```

## Build Limpo

Para limpar todos os arquivos gerados e reconstruir o projeto do zero:

1. **Remova o diretório `build`**:
   ```bash
   rm -rf build
   ```

2. **Repita o processo de build** a partir do passo 2.

## Execução

1. **Insira um arquivo .s dentro do diretório build**
2. **Execute o programa**

**OBS: os arquivos .s ou .asm DEVEM estar dentro da pasta build para serem executados
---
