// label_list.h
#ifndef LABEL_H
#define LABEL_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_LABELS 500
#define MAX_LABEL_LEN 100

// Definition of Label
typedef struct Label {
    char name[MAX_LABEL_LEN];          // Dynamically allocated name
    uint32_t address;    // Memory address associated with the label
} Label;

extern Label label_arr[];
extern uint32_t curr_label;

void add_label(Label *label_arr, const char *name, uint32_t address);
void print_label_list(Label *label_arr);
uint32_t find_label_address(Label *label_arr, const char *name);

#endif // LABEL_LIST_H
