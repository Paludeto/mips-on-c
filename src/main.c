  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  #include "../include/parser.h"

  #define MAX_INPUT_SIZE 256

int main(void) {

  initialize_memory();         

  init_registers(r_array);

  parseFile("test.s");
  // interactive_parse(r_array, &inst_list, &label_list);
  
  // // Table headers
  // printf("+-----------+------------+\n");
  // printf("| Register  | Value      |\n");
  // printf("+-----------+------------+\n");

  // // Table rows for each register
  // for (int i = 0; i < REG_NUM; i++) {
  //     printf("| %-9s | %-10d |\n", r_array[i].name, r_array[i].value);
  // }

  // // Table footer
  // printf("+-----------+------------+\n");

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
    }
}

  printf("%d\n", current_text_address);

  return 0;

}