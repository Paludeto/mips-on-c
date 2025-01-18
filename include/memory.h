#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdbool.h>

// Define memory size (1 MB for example)
#define MEMORY_SIZE 0x100000 // 1,048,576 bytes

extern unsigned char memory[];
extern uint32_t data_segment_start;
extern uint32_t text_segment_start;
extern uint32_t current_data_address;
extern uint32_t program_counter;

// Function to load a word from simulated memory (big-endian)
bool load_word_from_memory(uint32_t address, int *value);

// Function to store a word to simulated memory (big-endian)
bool store_word_to_memory(uint32_t address, int value);

// Function to store string address
bool store_string_to_memory(uint32_t address, const char *string);

// Initialize simulated memory
void initialize_memory();

#endif