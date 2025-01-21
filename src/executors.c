#include "executors.h"
#include "memory.h"
#include <stdio.h>

void execute_add(Instruction inst) {

    printf("Executing ADD with registers %d, %d, %d\n", inst.value.RType.rd, inst.value.RType.rs, inst.value.RType.rt);
    r_array[inst.value.RType.rd].value = r_array[inst.value.RType.rs].value + r_array[inst.value.RType.rt].value;

}

void execute_sub(Instruction inst) {

    printf("Executing SUB with registers %d, %d, %d\n", inst.value.RType.rd, inst.value.RType.rs, inst.value.RType.rt);
    r_array[inst.value.RType.rd].value = r_array[inst.value.RType.rs].value - r_array[inst.value.RType.rt].value;

}

void execute_mult(Instruction inst) {

    printf("Executing MULT with registers %d, %d, %d\n", inst.value.RType.rd, inst.value.RType.rs, inst.value.RType.rt);
    r_array[inst.value.RType.rd].value = r_array[inst.value.RType.rs].value * r_array[inst.value.RType.rt].value;

}

void execute_and(Instruction inst) {

    printf("Executing AND with registers %d, %d, %d\n", inst.value.RType.rd, inst.value.RType.rs, inst.value.RType.rt);
    r_array[inst.value.RType.rd].value = r_array[inst.value.RType.rs].value & r_array[inst.value.RType.rt].value;

}

void execute_or(Instruction inst) {

    printf("Executing OR with registers %d, %d, %d\n", inst.value.RType.rd, inst.value.RType.rs, inst.value.RType.rt);
    r_array[inst.value.RType.rd].value = r_array[inst.value.RType.rs].value | r_array[inst.value.RType.rt].value;

}

void execute_sll(Instruction inst) {

    printf("Executing SLL with registers %d, %d, shift %d\n", inst.value.RType.rd, inst.value.RType.rt, inst.value.RType.shamt);
    r_array[inst.value.RType.rd].value = r_array[inst.value.RType.rt].value << inst.value.RType.shamt;

}

void execute_slt(Instruction inst) {

    printf("Executing SLT with registers %d, %d, %d\n", inst.value.RType.rd, inst.value.RType.rs, inst.value.RType.rt);
    r_array[inst.value.RType.rd].value = (r_array[inst.value.RType.rs].value < r_array[inst.value.RType.rt].value) ? 1 : 0;

}

void execute_addi(Instruction inst) {

    printf("Executing ADDI with registers %d, %d, immediate %d\n", inst.value.IType.rt, inst.value.IType.rs, inst.value.IType.imm);
    r_array[inst.value.IType.rt].value = r_array[inst.value.IType.rs].value + inst.value.IType.imm;

}

void execute_slti(Instruction inst) {
    
    printf("Executing SLTI with registers %d, %d, immediate %d\n", inst.value.IType.rt, inst.value.IType.rs, inst.value.IType.imm);
    r_array[inst.value.IType.rt].value = r_array[inst.value.IType.rs].value < inst.value.IType.imm ? 1 : 0;

}

void execute_lui(Instruction inst) {

    printf("Executing LUI with register %d, immediate %d\n", inst.value.IType.rt, inst.value.IType.imm);
    r_array[inst.value.IType.rt].value = (int32_t)inst.value.IType.imm << 16;

}

void execute_lw(Instruction inst) {

    printf("Executing LW with register %d and offset %d(base %d)\n", inst.value.IType.rt, inst.value.IType.imm, inst.value.IType.rs);
    uint32_t address = r_array[inst.value.IType.rs].value + inst.value.IType.imm;
    int loaded_value;
    if (load_word_from_memory(address, &loaded_value)) {
        r_array[inst.value.IType.rt].value = loaded_value;
    } else {
        printf("Error: Failed to load word from memory at address %u\n", address);
    }

}

void execute_sw(Instruction inst) {

    printf("Executing SW with register %d and offset %d(base %d)\n", inst.value.IType.rt, inst.value.IType.imm, inst.value.IType.rs);
    uint32_t address = r_array[inst.value.IType.rs].value + inst.value.IType.imm;
    store_word_to_memory(address, r_array[inst.value.IType.rt].value);

}

void execute_pseudo_inst(Instruction inst) {

    printf("Executing Pseudo-Instruction: rt = %d\n", inst.value.PType.rt);

    if (inst.value.PType.is_label) {
        printf("Loading address 0x%08X into register %d\n", inst.value.PType.data.address, inst.value.PType.rt);
        r_array[inst.value.PType.rt].value = inst.value.PType.data.address;
    } else {
        printf("Loading immediate value %d into register %d\n", inst.value.PType.data.imm, inst.value.PType.rt);
        r_array[inst.value.PType.rt].value = inst.value.PType.data.imm;
    }

}

void execute_syscall(Instruction inst) {

    int syscall_code = r_array[2].value;

    switch (syscall_code) {
        case 4:
            printf("Output: %s\n", (char *)&data_memory[r_array[4].value]);
            break;
        case 10:
            printf("Exiting program...\n");
            return;
        default:
            printf("Error: Unsupported syscall code %d\n", syscall_code);
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
                printf("Executing R-Type instruction at index %d\n", pc);
                jump_table[current_inst.value.RType.funct](current_inst);
                pc++; // Move to the next instruction
                break;

            case I:

                printf("Executing I-Type instruction at index %d\n", pc);
                jump_table[current_inst.opcode](current_inst);
                pc++; // Move to the next instruction
                break;

            case J:
               
                printf("Executing J-Type instruction at index %d\n", pc);
                printf("Jumping to line: %u\n", current_inst.value.JType.address);
                execute_j(current_inst);  // Convert byte address to instruction index
                break;

            case P:

                printf("Executing Pseudo instruction at index %d\n", pc);
                execute_pseudo_inst(current_inst);
                pc++; // Move to the next instruction
                break;

            case SYS:

                printf("Executing Pseudo instruction at index %d\n", pc);
                execute_syscall(current_inst);
                pc++; // Prevent infinite loops on unknown instructions

                break;

            default:

                printf("Unknown instruction type at index %d\n", pc);
                pc++; // Prevent infinite loops on unknown instructions
                break;

        }
    }

}
