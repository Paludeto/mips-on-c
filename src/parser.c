// parser.c
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define maximums
#define MAX_OP 4
#define MAX_DIR 100
#define MAX_INPUT_SIZE 256
#define MAX_OPERANDS 4

// External variables from memory.c
extern uint32_t data_segment_start;
extern uint32_t current_data_address;

// Function to parse the entire file
void parseFile(char *file_name, Register *r_array, InstructionList *inst_list, LabelList *label_list) {
    
    FILE *fp = fopen(file_name, "r");
    char line[MAX_INPUT_SIZE];
    char current_mode[16] = "";

    if (fp == NULL) {
        perror("File could not be opened");
        return;
    }
    
    initialize_memory();

    // Initialize data address
    if (current_data_address == 0) {
        current_data_address = data_segment_start;
    }

    while (fgets(line, sizeof(line), fp)) {
        // Remove newline characters
        size_t len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[len - 1] = '\0';
            len--;
        }

        // Remove comments
        char *comment = strchr(line, '#');
        if (comment) *comment = '\0';

        // Trim leading whitespace
        char *start = line;
        while (isspace(*start)) start++;

        if (*start == '\0') continue; // Skip empty lines

        tokenize_line(start, r_array, inst_list, label_list, current_mode);
    }

    fclose(fp);

}

void tokenize_line(char *line, Register *r_array, InstructionList *inst_list, LabelList *label_list, char *current_mode) {
    // Updated delimiters to exclude '(' and ')'
    const char delimiters[] = " \t,";
    char *token = strtok(line, delimiters);

    if (token == NULL) return; // Empty line

    // Check for label (ends with ':')
    size_t token_len = strlen(token);
    if (token[token_len - 1] == ':') {
        token[token_len - 1] = '\0'; // Remove ':'
        // Create label with current_data_address or instruction address based on current_mode
        uint32_t label_address = (strcasecmp(current_mode, ".data") == 0) ? current_data_address : 0; // Assign 0 for text labels initially
        Label *newLabel = create_label(token, label_address);
        if (!newLabel) {
            printf("Error: Failed to create label %s\n", token);
            return;
        }
        add_label(label_list, newLabel);
        token = strtok(NULL, delimiters); // Get next token after label
        if (token == NULL) return; // Line has only label
    }

    // Check for section markers
    if (is_data_field(token)) {
        strcpy(current_mode, ".data");
        return;
    } else if (is_text_field(token)) {
        strcpy(current_mode, ".text");
        // Optionally, reset current_text_address here if you have separate addresses
        return;
    }

    if (strcasecmp(current_mode, ".data") == 0) {
        // Process data directives
        char *args[MAX_DIR];
        int arg_count = 0;

        args[arg_count++] = token; // Directive

        while ((token = strtok(NULL, delimiters)) != NULL) {
            args[arg_count++] = token;
        }

        if (arg_count > 0) {
            validate_data_field(NULL, args, arg_count, label_list);
        }
    } else if (strcasecmp(current_mode, ".text") == 0) {
        // Process instructions
        char *instruction = token;
        char *operands[MAX_OPERANDS];
        int operand_count = 0;

        while ((token = strtok(NULL, delimiters)) != NULL) {
            operands[operand_count++] = token;
            if (operand_count >= MAX_OPERANDS) break;
        }

        validate_execute_inst(instruction, operands, operand_count, r_array, inst_list, label_list);
    }

}

// Validate operands based on instruction definition
bool validate_operands(const Instruction *inst_def, char **operands, int operand_count) {
    // Corrected member name from operand_count to op_count
    if (inst_def->op_count != operand_count) {
        // Corrected member names from operation to name and operand_count to op_count
        printf("Error: %s expects %d operands, found %d\n", inst_def->name, inst_def->op_count, operand_count);
        return false;
    }

    // Additional operand validation based on instruction type can be added here

    return true;
}

// Validate and execute an instruction
void validate_execute_inst(const char *instruction, char **operands, int operand_count, Register *r_array, InstructionList *inst_list, LabelList *label_list) {

    Instruction *inst_def = find_instruction(instruction);

    if (!inst_def) {
        printf("Error: Unknown instruction: %s\n", instruction);
        return;
    }

    if (!validate_operands(inst_def, operands, operand_count)) {
        return;
    }

    // Corrected create_instruction call to include InstructionType
    Instruction *inst = create_instruction(instruction, inst_def->type, operands, operand_count);
    if (!inst) {
        printf("Error: Failed to create instruction %s\n", instruction);
        return;
    }

    // Execute the instruction using function pointers
    if (inst_def->basic_executor != NULL) {
        inst_def->basic_executor(inst->operands, r_array);
    } else if (inst_def->label_executor != NULL) {
        inst_def->label_executor(inst->operands, r_array, label_list);
    }

    // Add instruction to the list
    add_instruction(inst_list, inst);

}

// Validate and handle data directives
void validate_data_field(const char *label_name, char **args, int arg_count, LabelList *label_list) {

    if (arg_count < 2) { // Minimum: directive and at least one value
        printf("Error: Insufficient arguments in data field\n");
        return;
    }

    // Validate the directive
    if (!is_directive(args[0])) {
        printf("Error: Invalid directive in data field: %s\n", args[0]);
        return;
    }

    // Handle directives (e.g., .word, .byte, .space)
    if (strcasecmp(args[0], ".word") == 0) {
        // Each subsequent argument is a word to store
        for (int i = 1; i < arg_count; i++) {
            // Convert to integer
            char *endptr;
            long value_long = strtol(args[i], &endptr, 10);
            if (*endptr != '\0') {
                printf("Error: Invalid immediate value: %s\n", args[i]);
                continue;
            }
            uint32_t value = (uint32_t)value_long;

            // Store in simulated memory
            if (!store_word_to_memory(current_data_address, value)) {
                printf("Error: Failed to store word at address 0x%X\n", current_data_address);
                return;
            }

            // If it's the first word and label_name is provided, map the label to this address
            if (i == 1 && label_name != NULL) {
                Label *newLabel = create_label(label_name, current_data_address);
                if (!newLabel) {
                    printf("Error: Failed to create label %s\n", label_name);
                    return;
                }
                add_label(label_list, newLabel);
            }

            // Increment the data address by 4 bytes (size of a word)
            current_data_address += 4;
        }
    }
    // Implement other directives like .byte, .half, .space as needed
    else {
        printf("Error: Unsupported directive %s in data field\n", args[0]);
    }

}

// Helper functions
bool is_op(const char *token) {

    if (token == NULL) {
        return false;
    }

    if (get_register_index(token) == -1) {
        return false;
    }

    return is_imm(token);

}

bool is_imm(const char *token) {

    if (*token == '-' || *token == '+') {
        token++;
    }

    if (*token == '\0') {
        return false;       
    }

    while (*token) {
        if (!isdigit(*token)) {
            return false;
        }
        token++;
    }

    return true;

}

bool is_address(const char *token) {

    if (token == NULL) {
        return false;
    }

    char *open_paren = strchr(token, '(');
    char *closed_paren = strchr(token, ')');

    if (open_paren == NULL || closed_paren == NULL) {
        return false;
    }

    // Extract the register name inside parentheses
    size_t reg_len = closed_paren - open_paren - 1;
    if (reg_len <= 0 || reg_len >= 8) { // Assuming max register name length is 7
        return false;
    }

    char reg[8];
    strncpy(reg, open_paren + 1, reg_len);
    reg[reg_len] = '\0';

    if (get_register_index(reg) == -1) {
        return false;
    }

    // Check the offset part
    size_t offset_len = open_paren - token;
    if (offset_len <= 0 || offset_len >= 16) { // Assuming max offset length
        return false;
    }

    char offset_str[16];
    strncpy(offset_str, token, offset_len);
    offset_str[offset_len] = '\0';

    // Validate offset is a number
    char *endptr;
    strtol(offset_str, &endptr, 10);
    if (*endptr != '\0') {
        return false;
    }

    return true;

}

bool is_data_field(const char *token) {
    return strcasecmp(token, ".data") == 0 || strcasecmp(token, ".data:") == 0;
}

bool is_text_field(const char *token) {
    return strcasecmp(token, ".text") == 0;
}

bool is_directive(const char *token) {

    const char *directives[] = {".word", ".byte", ".half", ".float", ".double", ".space", NULL};

    for (int i = 0; directives[i] != NULL; i++) {
        if (strcmp(token, directives[i]) == 0) {
            return true; // Valid directive found
        }
    }

    return false;

}