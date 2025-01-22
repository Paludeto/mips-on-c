#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"

// Initialize memory array
unsigned char data_memory[DATA_MEM_SIZE];
Instruction inst_memory[INST_MEM_SIZE];

// Define the start address of the data segment (e.g., 0x00010000)
uint32_t current_text_address = 0;
uint32_t current_data_address = 0;

// Initialize memory (optional: set to zero)
void initialize_memory() {
    memset(data_memory, 0, sizeof(data_memory));
    memset(inst_memory, 0, sizeof(inst_memory));
}

// Function to load a word from simulated memory (big-endian)
bool load_word_from_memory(uint32_t address, int *value) {

    if (address >= DATA_MEM_SIZE - 3) {
        fprintf(stderr, "Memory access violation at address: 0x%X\n", address);
        return false;
    }

    if (address % 4 != 0) {
        fprintf(stderr, "Unaligned memory access at address: 0x%X\n", address);
        return false;
    }

    // Load 4 bytes and construct the word (big-endian)
    *value = (data_memory[address] << 24) |
             (data_memory[address + 1] << 16) |
             (data_memory[address + 2] << 8) |
             (data_memory[address + 3]);

    return true;

}

// Function to store a word to simulated memory (big-endian)
bool store_word_to_memory(uint32_t address, int value) {

    if (address >= DATA_MEM_SIZE - 3) {
        fprintf(stderr, "Memory access violation at address: 0x%X\n", address);
        return false;
    }
    if (address % 4 != 0) {
        fprintf(stderr, "Unaligned memory access at address: 0x%X\n", address);
        return false;
    }
    
    data_memory[address]     = (value >> 24) & 0xFF;
    data_memory[address + 1] = (value >> 16) & 0xFF;
    data_memory[address + 2] = (value >> 8) & 0xFF;
    data_memory[address + 3] = value & 0xFF;
    
    return true;

}

bool store_string_to_memory(uint32_t address, const char *string) {

    size_t len = strlen(string) + 1; // Include null terminator
    
    if (address + len > DATA_MEM_SIZE) {
        fprintf(stderr, "Memory access violation: String exceeds memory bounds\n");
        return false;
    }

    memcpy(&data_memory[address], string, len); // Copy string to memory

    return true;

}

bool store_instruction_to_memory(uint32_t address, Instruction instruction) {

    if (address > INST_MEM_SIZE) {
        fprintf(stderr, "Insufficient instruction memory\n");
        return false;
    }

    inst_memory[address] = instruction;

    return true;

}
