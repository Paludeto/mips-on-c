#ifndef ENCODER_H
#define ENCODER_H

#include "instructions.h"

/**
 * @brief Encodes the instruction into binary
 * 
 * @param inst 
 * @return int 
 */
int encode_instruction(Instruction inst);

/**
 * @brief Encodes the entire instruction array to binary
 * 
 * @param inst_arr 
 */
void encode_inst_arr(Instruction *inst_arr);

/**
 * @brief Prints the binary representation of a number
 * 
 * @param num 
 */
void print_binary(int num);

#endif