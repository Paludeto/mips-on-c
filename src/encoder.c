#include "encoder.h"

int encode(Instruction *inst, char **operands) {
    
    int binary = 0;
    int opcode = 0;
    int funct = 0;

    switch (inst->type) {

        case R: {

            int shamt = 0;
            int rd = get_register_index(operands[0]); 
            int rs = get_register_index(operands[1]); 
            int rt = get_register_index(operands[2]); 

            if (rt == -1) {
                shamt = atoi(operands[2]);
                rt = 0;
            }

            if (strcmp(inst->name, "add") == 0) {
                funct = 0x20; 
            } else if (strcmp(inst->name, "sub") == 0) {
                funct = 0x22; 
            } else if (strcmp(inst->name, "mult") == 0) {
                funct = 0x18; 
                rd = 0; 
            } else if (strcmp(inst->name, "and") == 0) {
                funct = 0x24; 
            } else if (strcmp(inst->name, "or") == 0) {
                funct = 0x25; 
            } else if (strcmp(inst->name, "sll") == 0) {
                funct = 0x00; 
            } else if (strcmp(inst->name, "slt") == 0) {
                funct = 0x2A; 
            } else if (strcmp(inst->name, "move") == 0) {
                funct = 0x20; 
                rs = 0;      
            } else {
                printf("Error: Unsupported R-type instruction '%s'\n", inst->name);
                return -1;
            }
            
            binary = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;

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