  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  #include "../include/parser.h"

  #define MAX_INPUT_SIZE 256

int main(void) {

  initialize_memory();         
  LabelList label_list;

  init_registers(r_array);
  init_label_list(&label_list);

  parseFile("test.s");
  // interactive_parse(r_array, &inst_list, &label_list);

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

  free_label_list(&label_list);

  return 0;

}