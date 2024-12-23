#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "instruction.h"
#include "instruction_list.h"

// Function prototypes
InstructionTable *find_instruction(const char *name);
Instruction *create_instruction(const char *name, char **operands, int op_count);
void free_instruction(Instruction *inst);
bool validate_operands(const InstructionTable *inst_def, char **operands, int operand_count);
void validate_and_execute(const char *instruction, char **operands, int operand_count, Register *r_array, InstructionList *inst_list);

// Execution functions
int get_register_index(const char *reg);

void tokenize_line(char *line, Register *r_array, InstructionList *inst_list);
bool is_reg(const char *token);
bool is_label(const char *token);
bool is_inst(const char *token);
bool is_op(const char *token);
bool is_imm(const char *token);
bool is_address(const char *token);
bool is_data_field(const char *token);
bool is_text_field(const char *token);
bool is_directive(const char *token);
void test_fn(char *token);
void validate_instruction(char *instruction, char **operands, int operand_count, Register *r_array, InstructionList *inst_list);
void create_inst(char *instruction, char **operands, int operand_count, Instruction *new_inst, Register *r_array, InstructionList *inst_list, InstructionType type) ;

#endif