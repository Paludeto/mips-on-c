#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "instruction_list.h"
#include "label_list.h"
#include "memory.h"

// Function prototypes
void interactive_parse(Register *r_array, InstructionList *inst_list, LabelList *label_list);
void parseFile(char *file_name, Register *r_array, InstructionList *inst_list, LabelList *label_list);
void tokenize_line(char *line, Register *r_array, InstructionList *inst_list, LabelList *label_list, char *current_mode);
bool validate_operands(const Instruction *inst_def, char **operands, int operand_count);
void validate_execute_inst(const char *instruction, char **operands, int operand_count, Register *r_array, InstructionList *inst_list, LabelList *label_list);
void validate_data_field(const char *token, char **args, int arg_count, LabelList *label_list);
bool is_label(const char *token);
bool is_op(const char *token);
bool is_immediate(const char *token);
bool is_address(const char *token);
bool is_data_field(const char *token);
bool is_text_field(const char *token);
bool is_directive(const char *token);
bool is_register(const char *token);

#endif