#include <stdio.h>
#include <stdlib.h>

#include "executors.h"
#include "register.h"
#include "memory.h"   
#include "encoder.h"

void execute_add(Instruction inst) {

    r_array[inst.value.RType.rd].value = r_array[inst.value.RType.rs].value + r_array[inst.value.RType.rt].value;

}

void execute_sub(Instruction inst) {

    r_array[inst.value.RType.rd].value = r_array[inst.value.RType.rs].value - r_array[inst.value.RType.rt].value;

}

void execute_mult(Instruction inst) {

    r_array[inst.value.RType.rd].value = r_array[inst.value.RType.rs].value * r_array[inst.value.RType.rt].value;

}

void execute_and(Instruction inst) {

    r_array[inst.value.RType.rd].value = r_array[inst.value.RType.rs].value & r_array[inst.value.RType.rt].value;

}

void execute_or(Instruction inst) {

    r_array[inst.value.RType.rd].value = r_array[inst.value.RType.rs].value | r_array[inst.value.RType.rt].value;

}

void execute_sll(Instruction inst) {

    r_array[inst.value.RType.rd].value = r_array[inst.value.RType.rt].value << inst.value.RType.shamt;

}

void execute_slt(Instruction inst) {

    r_array[inst.value.RType.rd].value = (r_array[inst.value.RType.rs].value < r_array[inst.value.RType.rt].value) ? 1 : 0;

}

void execute_addi(Instruction inst) {

    r_array[inst.value.IType.rt].value = r_array[inst.value.IType.rs].value + inst.value.IType.imm;

}

void execute_slti(Instruction inst) {
    
    r_array[inst.value.IType.rt].value = r_array[inst.value.IType.rs].value < inst.value.IType.imm ? 1 : 0;

}

void execute_lui(Instruction inst) {

    r_array[inst.value.IType.rt].value = (int32_t)inst.value.IType.imm << 16;

}

void execute_lw(Instruction inst) {

    uint32_t address = r_array[inst.value.IType.rs].value + inst.value.IType.imm;
    int loaded_value;
    if (load_word_from_memory(address, &loaded_value)) {
        r_array[inst.value.IType.rt].value = loaded_value;
    } else {
        printf("Error: Failed to load word from memory at address %u\n", address);
        exit(EXIT_FAILURE);
    }

}

void execute_sw(Instruction inst) {

    uint32_t address = r_array[inst.value.IType.rs].value + inst.value.IType.imm;
    store_word_to_memory(address, r_array[inst.value.IType.rt].value);

}

void execute_pseudo_inst(Instruction inst) {

    if (inst.value.PType.is_label) {
        r_array[inst.value.PType.rt].value = inst.value.PType.data.address;
    } else {
        r_array[inst.value.PType.rt].value = inst.value.PType.data.imm;
    }

}

void execute_syscall(Instruction inst) {

    int syscall_code = r_array[2].value;

    switch (syscall_code) {
        case 1:
            printf("%d\n", r_array[4].value);
            break;
        case 4:
            printf("%s\n", (char *)&data_memory[r_array[4].value]);
            break;
        case 10:
            printf("Exiting program...\n");
            break;
        default:
            printf("Error: Unsupported syscall code %d\n", syscall_code);
            exit(EXIT_FAILURE);
            break;
    }

}

void execute_j(Instruction inst) {

    pc = inst.value.JType.address;

}

void execute_instructions() {

    while (pc < current_text_address) {

        Instruction current_inst = inst_memory[pc];
    
        switch (current_inst.type) {

            case R:
   
                jump_table[current_inst.value.RType.funct](current_inst);
                pc++; // Move to the next instruction
                break;

            case I:

                jump_table[current_inst.opcode](current_inst);
                pc++; // Move to the next instruction
                break;

            case J:

                execute_j(current_inst);  // Convert byte address to instruction index
                break;

            case P:

                execute_pseudo_inst(current_inst);
                pc++; // Move to the next instruction
                break;

            default:
        
                pc++; // Prevent infinite loops on unknown instructions
                break;

        }
    }

}
