#ifndef ENCODER_H
#define ENCODER_H

#include "instructions.h"

int encode_instruction(Instruction inst);
void encode_inst_arr(Instruction *inst_arr);
void print_binary(int num);

#endif