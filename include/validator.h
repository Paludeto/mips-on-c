#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "instructions.h"
#include "label.h"

bool validate_operands(const InstructionInfo *inst_def, char **operands, int operand_count);
void validate_inst(const char *instruction, char **operands, int operand_count);
void validate_data_field(const char *label_name, char **args, int arg_count, Label *label_arr);
bool extract_op(const InstructionInfo *inst_def, char **operands, int operand_count);
int extract_register(const char *operand);
int extract_address(const char *operand);

bool is_label(const char *token);
bool is_op(const char *token);
bool is_immediate(const char *token);
bool is_address(const char *token);
bool is_data_field(const char *token);
bool is_text_field(const char *token);
bool is_directive(const char *token);
bool is_register(const char *token);

#endif