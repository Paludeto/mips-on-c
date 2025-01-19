
#include "label.h"

Label label_arr[MAX_LABELS];
uint32_t curr_label = 0;

// Add a label to the list
void add_label(Label *label_arr, const char *name, uint32_t address) {

    if (curr_label >= MAX_LABELS) {
        fprintf(stderr, "Max amount of labels reached\n");
        return;
    }

    label_arr[curr_label].address = address;
    strncpy(label_arr[curr_label].name, name, MAX_LABEL_LEN - 1); // Copy name to label's field
    label_arr[curr_label].name[MAX_LABEL_LEN - 1] = '\0';         // Ensure null termination

    curr_label++;

}

// Print all labels in the list
void print_label_list(Label *label_arr) {

    for (int i = 0; i < curr_label; i++) {
        printf("%s, 0x%X\n", label_arr[i].name, label_arr[i].address);
    }

}

// Find a label by name and return its address
uint32_t find_label_address(Label *label_arr, const char *name) {

    for (int i = 0; i < curr_label; i++) {

        if (strcmp(name, label_arr[i].name) == 0) {
            return label_arr[i].address;
        }

    }

    return -1;

}