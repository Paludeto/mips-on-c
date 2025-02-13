#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdbool.h>

#include "instructions.h"

// Define memory size (could be optimized for embedded systems and whatnot)
#define DATA_MEM_SIZE 0x200000 // 2 MB
#define INST_MEM_SIZE 0x100000 // 1 MB

extern unsigned char data_memory[];
extern Instruction inst_memory[];

extern uint32_t current_text_address;
extern uint32_t current_data_address;
extern uint32_t program_counter;

// Function to load a word from simulated memory (big-endian)
bool load_word_from_memory(uint32_t address, int *value);

// Function to store a word from simulated memory (big-endian)
bool store_word_to_memory(uint32_t address, int value);

// Function to store string address
bool store_string_to_memory(uint32_t address, const char *string);

// Instruction storage
bool store_instruction_to_memory(uint32_t address, Instruction instruction);

// Initialize simulated memory
void initialize_memory();

#endif