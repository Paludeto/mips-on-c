#include "encoder.h"

int encode(Instruction *inst, char **operands) {
    
    int binary = 0;
    int opcode = 0;
    int funct = 0;

    switch (inst->type) {

        case R: {

            int shamt = 0;
            int rd, rs, rt;

            if (inst->op_count == 2) {
                rd = 0;
                rs = get_register_index(operands[0]);
                rt = get_register_index(operands[1]); 
            } else if (inst->op_count == 3) {
                rd = get_register_index(operands[0]); 
                rs = get_register_index(operands[1]); 
                rt = get_register_index(operands[2]);

                if (strcmp(inst->name, "sll") == 0) {
                    rs = 0;
                    rt = get_register_index(operands[1]);
                    rd = get_register_index(operands[0]);  
                    shamt = atoi(operands[2]);  
                }

            } else {
                printf("Unsupported instruction\n");
                return -1;
            }
            
            binary = (inst->opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | inst->funct;

            break;
            
        } 

        case I: {

        }   

        case J: {

        }  

        case P: {

        }

        /*case SYS: {

        }*/

    }

    return binary;

}