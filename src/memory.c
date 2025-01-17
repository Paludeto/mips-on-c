// memory.c
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialize memory array
unsigned char memory[MEMORY_SIZE];

// Define the start address of the data segment (e.g., 0x00010000)
uint32_t data_segment_start = 0x00010000;

// Initialize the current data address to the start of the data segment
uint32_t current_data_address = 0;

// Initialize memory (optional: set to zero)
void initialize_memory() {
    memset(memory, 0, sizeof(memory));
}

// Function to load a word from simulated memory (big-endian)
bool load_word_from_memory(uint32_t address, int *value) {

    if (address >= MEMORY_SIZE - 3) {
        fprintf(stderr, "Memory access violation at address: 0x%X\n", address);
        return false;
    }

    if (address % 4 != 0) {
        fprintf(stderr, "Unaligned memory access at address: 0x%X\n", address);
        return false;
    }

    // Load 4 bytes and construct the word (big-endian)
    *value = (memory[address] << 24) |
             (memory[address + 1] << 16) |
             (memory[address + 2] << 8) |
             (memory[address + 3]);

    return true;

}

// Function to store a word to simulated memory (big-endian)
bool store_word_to_memory(uint32_t address, int value) {

    if (address >= MEMORY_SIZE - 3) {
        fprintf(stderr, "Memory access violation at address: 0x%X\n", address);
        return false;
    }
    if (address % 4 != 0) {
        fprintf(stderr, "Unaligned memory access at address: 0x%X\n", address);
        return false;
    }
    
    memory[address]     = (value >> 24) & 0xFF;
    memory[address + 1] = (value >> 16) & 0xFF;
    memory[address + 2] = (value >> 8) & 0xFF;
    memory[address + 3] = value & 0xFF;
    return true;

}

bool store_string_to_memory(uint32_t address, const char *string) {
    size_t len = strlen(string) + 1; // Include null terminator
    if (address + len > MEMORY_SIZE) {
        fprintf(stderr, "Memory access violation: String exceeds memory bounds\n");
        return false;
    }
    memcpy(&memory[address], string, len); // Copy string to memory
    return true;
}
