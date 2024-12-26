#ifndef LABEL_LIST_H
#define LABEL_LIST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum LabelType {
    CODE,
    DATA
} LabelType;

// Definition of Label
typedef struct Label {
    char *name;
    int32_t *data;
    int address;
    LabelType type;
} Label;

// Node structure for Label list
typedef struct LabelNode {
    Label label;
    struct LabelNode *next;
} LabelNode;

// List structure for managing Labels
typedef struct LabelList {
    LabelNode *head;
    int size;
} LabelList;

// Function prototypes
void init_label_list(LabelList *list);
Label *create_label(const char *name, LabelType type, int32_t *data, int32_t address);
void add_label(LabelList *list, Label *label);
void print_label_list(LabelList *list);
void free_label_list(LabelList *list);

#endif // LABEL_LIST_H