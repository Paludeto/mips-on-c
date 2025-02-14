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
