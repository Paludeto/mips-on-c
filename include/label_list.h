// label_list.h
#ifndef LABEL_LIST_H
#define LABEL_LIST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

// Definition of Label
typedef struct Label {
    char *name;          // Dynamically allocated name
    uint32_t address;    // Memory address associated with the label
} Label;

// Node structure for Label list
typedef struct LabelNode {
    Label *label;
    struct LabelNode *next;
} LabelNode;

// List structure for managing Labels
typedef struct LabelList {
    LabelNode *head;
    int size;
} LabelList;

// Function prototypes
void init_label_list(LabelList *list);
Label *create_label(const char *name, uint32_t address);
Label *find_label(LabelList *list, const char *name);
void add_label(LabelList *list, Label *label);
void print_label_list(const LabelList *list);
void free_label(Label *label);
void free_label_list(LabelList *list);

#endif // LABEL_LIST_H
