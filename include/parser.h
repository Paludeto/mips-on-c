#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "instruction.h"
#include "instruction_list.h"

// Instruction validation and execution
bool validate_operands(const Instruction *inst_def, char **operands, int operand_count);
void validate_and_execute(const char *instruction, char **operands, int operand_count, Register *r_array, InstructionList *inst_list);

void tokenize_line(char *line, Register *r_array, InstructionList *inst_list);

// Check tokens
bool is_label(const char *token);
bool is_inst(const char *token);
bool is_op(const char *token);
bool is_imm(const char *token);
bool is_address(const char *token);
bool is_data_field(const char *token);
bool is_text_field(const char *token);
bool is_directive(const char *token);

// Test check
void test_fn(char *token);

#endif