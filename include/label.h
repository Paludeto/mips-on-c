#ifndef LABEL_H
#define LABEL_H

#include <stdint.h>

#define MAX_LABELS 500
#define MAX_LABEL_LEN 100

typedef struct Label {
    char name[MAX_LABEL_LEN];
    uint32_t address; 
} Label;

extern Label label_arr[];
extern uint32_t curr_label;

void add_label(const char *name, uint32_t address);
void print_label_list();
uint32_t find_label_address(const char *name);

#endif // LABEL_LIST_H
