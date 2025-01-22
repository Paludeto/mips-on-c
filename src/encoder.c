#include "encoder.h"

int encode_instruction(Instruction inst) {


    int binary = -1;

    switch (inst.type) {   

        case R: 
            
            binary = (inst.opcode << 26) | (inst.value.RType.rs << 21) | (inst.value.RType.rt << 16) | 
                (inst.value.RType.rd << 11) | (inst.value.RType.shamt << 6) | inst.value.RType.funct;

            break;
        

        case I: 

            binary = (inst.opcode << 26) | (inst.value.IType.rs << 21) | 
                (inst.value.IType.rt << 16) | inst.value.IType.imm;

            break;

        case J:  

            binary = (inst.opcode << 26) | (inst.value.JType.address & 0x03FFFFFF);

            break;
            
        default:

            printf("Pseudo-instruction cannot be encoded\n");
            break;
    }

    return binary;

}

void print_binary(int num) {

    for (int i = 31; i >= 0; i--) {  
        printf("%d", (num >> i) & 1);  // Print each bit
    }

    printf("\n");

}

void encode_inst_arr(Instruction *inst_arr) {

    int inst_bin;

    for (int i = 0; i < current_text_address; i++) {

        inst_bin = encode_instruction(inst_arr[i]);

        if (inst_bin == -1 && inst_arr[i].type == P) {
            printf("Instruction at index %d is a pseudo-instruction\n", i);
        } else {
            print_binary(inst_bin);
            printf("\n");
        }

    }

}