#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"
#include "executors.h"

int main(void) {

	initialize_memory();         

	init_registers(r_array);

	parseFile("test.s");


	for (int i = 0; i < current_text_address; i++) {

		if (inst_memory[i].type == R) {
			printf("RType opcode: %d, rs: %d, rt: %d, rd: %d, shamt: %d, funct: %d\n",
				inst_memory[i].opcode,
				inst_memory[i].value.RType.rs,
				inst_memory[i].value.RType.rt,
				inst_memory[i].value.RType.rd,
				inst_memory[i].value.RType.shamt,
				inst_memory[i].value.RType.funct);

		} else if (inst_memory[i].type == I) {
			printf("IType opcode: %d, rs: %d, rt: %d, imm: %d\n",
				inst_memory[i].opcode,
				inst_memory[i].value.IType.rs,
				inst_memory[i].value.IType.rt,
				inst_memory[i].value.IType.imm);

		} else if (inst_memory[i].type == J) {
			uint32_t full_address = inst_memory[i].value.JType.address << 2;
			printf("JType opcode: %d, raw address: %d, full address: 0x%08X\n",
				inst_memory[i].opcode,
				inst_memory[i].value.JType.address,
				full_address);

		} else if (inst_memory[i].type == P) {
			if (inst_memory[i].value.PType.is_label) {
				printf("PType (LA) opcode: %d, rt: %d, address: %d\n",
					inst_memory[i].opcode,
					inst_memory[i].value.PType.rt,
					inst_memory[i].value.PType.data.address);
			} else {
				printf("PType (LI) opcode: %d, rt: %d, immediate: %d\n",
					inst_memory[i].opcode,
					inst_memory[i].value.PType.rt,
					inst_memory[i].value.PType.data.imm);
			}
		}
	}

	for (int i = 0; i < current_text_address; i++) {
		if (inst_memory[i].type == R) {
			jump_table[inst_memory[i].value.RType.funct](inst_memory[i]);
		} else if (inst_memory[i].type == I) {
			jump_table[inst_memory[i].opcode](inst_memory[i]);
		} else if (inst_memory[i].type == P) {
			execute_pseudo_inst(inst_memory[i]);
		} else if (inst_memory[i].type == SYS) {
			execute_syscall(inst_memory[i]);
		}
	}
		// Table headers
	printf("+-----------+------------+\n");
	printf("| Register  | Value      |\n");
	printf("+-----------+------------+\n");

	// Table rows for each register
	for (int i = 0; i < REG_NUM; i++) {
		printf("| %-9s | %-10d |\n", r_array[i].name, r_array[i].value);
	}

	// Table footer
	printf("+-----------+------------+\n");

	return 0;

}