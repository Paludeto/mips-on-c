#include "validator.h"

extern uint32_t current_data_address;
extern uint32_t current_text_address;
extern uint32_t program_counter;

// Validate and execute an instruction
void validate_inst(const char *instruction, char **operands, int operand_count) {

    Instruction *inst_def = find_instruction(instruction);

    if (!inst_def) {
        printf("Error: Unknown instruction: %s\n", instruction);
        return;
    }

    if (!validate_operands(inst_def, operands, operand_count)) {
        return;
    }


    printf("%s %s, %s, %s\n", instruction, operands[0], operands[1], operands[2]);
    int binary = encode(inst_def, operands);
    printf("Encoded instruction: 0x%08X\n", binary);

    if (store_instruction_to_memory(current_text_address, binary)) {
        fprintf(stderr, "Instruction stored\n");
        current_text_address++;
    } else {
        fprintf(stderr, "Instruction storage failed\n");
    }
    
}

// Validate operands based on instruction definition
bool validate_operands(const Instruction *inst_def, char **operands, int operand_count) {
    // Check if the operand count matches
    if (inst_def->op_count != operand_count) {
        printf("Error: %s expects %d operands, found %d\n", inst_def->name, inst_def->op_count, operand_count);
        return false;
    }
    
    // Validate operands based on InstructionType
    switch (inst_def->type) {

        case R:

            //SLL
            if (is_immediate(operands[2])) {
                for (int i = 0; i < operand_count - 1; i++) {
                    if (!is_register(operands[i])) {
                        printf("Error: Operand %d (%s) is not a valid register for instruction %s\n",
                            i + 1, operands[i], inst_def->name);
                        return false;
                    }
                }
            // mult
            } else if (strcmp(inst_def->name, "mult")) {

                if (is_register(operands[0]) && is_register(operands[1])) {
                    return true;
                }

                return false;

            } else {    // Other R-type instructions
                for (int i = 0; i < operand_count; i++) {
                    if (!is_register(operands[i])) {
                        printf("Error: Operand %d (%s) is not a valid register for instruction %s\n",
                            i + 1, operands[i], inst_def->name);
                        return false;
                    }
                }
            }

            break;

        case I:
            if (strcmp(inst_def->name, "lw") == 0 || strcmp(inst_def->name, "sw") == 0) {
                
                if (!is_register(operands[0])) {
                    printf("Error: Operand 1 (%s) is not a valid register for instruction %s\n",
                           operands[0], inst_def->name);
                    return false;
                }
                if (!is_address(operands[1])) {
                    printf("Error: Operand 2 (%s) is not a valid address for instruction %s\n",
                           operands[1], inst_def->name);
                    return false;
                }

            } else {
                // Standard I-Type: operand[0] and operand[1] are registers, operand[2] is immediate
                if (!is_register(operands[0])) {
                    printf("Error: Operand 1 (%s) is not a valid register for instruction %s\n",
                           operands[0], inst_def->name);
                    return false;
                }

                if (!is_register(operands[1])) {
                    printf("Error: Operand 2 (%s) is not a valid register for instruction %s\n",
                           operands[1], inst_def->name);
                    return false;
                }

                if (!is_immediate(operands[2])) {
                    printf("Error: Operand 3 (%s) is not a valid immediate for instruction %s\n",
                           operands[2], inst_def->name);
                    return false;
                }
            }

            break;

        case P:

            if (strcmp(inst_def->name, "li") == 0) {

                if (!is_register(operands[0])) {
                    printf("Error: Operand 1 (%s) is not a valid register for instruction %s\n",
                    operands[0], inst_def->name);
                    return false;
                }

                if (!is_immediate(operands[1])) {
                    printf("Error: Operand 2 (%s) is not a valid immediate for instruction %s\n",
                    operands[1], inst_def->name);
                    return false;
                }

                return true;

            } else {

                // P-Type: operand[0] is register, operand[1] is label
                if (!is_register(operands[0])) {
                    printf("Error: Operand 1 (%s) is not a valid register for instruction %s\n",
                        operands[0], inst_def->name);
                    return false;
                }

                if (!is_label(operands[1])) {
                    printf("Error: Operand 2 (%s) is not a valid label for instruction %s\n",
                        operands[1], inst_def->name);
                    return false;
                }


            }

            break;

        case SYS:

            if (operand_count != 0) {
                printf("Error: syscall takes no arguments\n");
                return false;
            }

            break;

        default:
            printf("Error: Unsupported instruction type for %s\n", inst_def->name);
            return false;
    }

    return true;

}

// Validate and handle data directives
void validate_data_field(const char *label_name, char **args, int arg_count) {

    if (arg_count < 2) { // Minimum: directive and at least one value
        printf("Error: Insufficient arguments in data field\n");
        return;
    }

    // Validate the directive
    if (!is_directive(args[0])) {
        printf("Error: Invalid directive in data field: %s\n", args[0]);
        return;
    }

    // Handle `.word` directive
    if (strcasecmp(args[0], ".word") == 0) {
        // Align the current_data_address to 4 bytes
        if (current_data_address % 4 != 0) {
            current_data_address += 4 - (current_data_address % 4);
        }

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

            // Increment the data address by 4 bytes (size of a word)
            current_data_address += 4;
        }

    } else if (strcasecmp(args[0], ".asciiz") == 0) {
        // Ensure label exists
        if (label_name == NULL) {
            printf("Error: Missing label for string directive.\n");
            return;
        }

        // Combine arguments into a single string
        char string_value[256] = "";
        for (int i = 1; i < arg_count; i++) {
            strcat(string_value, args[i]);
            if (i < arg_count - 1) strcat(string_value, " ");
        }

        // Store the string in memory
        if (!store_string_to_memory(current_data_address, string_value)) {
            printf("Error: Failed to store string at address 0x%X\n", current_data_address);
            return;
        }
        // Update the data address
        current_data_address += strlen(string_value) + 1; // +1 for null terminator
    } else {
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

    return is_immediate(token);

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

bool is_register(const char *token) {

    return (get_register_index(token) != -1);
     
}

bool is_immediate(const char *token) {

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

bool is_label(const char *token) {

    if (token == NULL || *token == '\0') {
        return false;
    }

    // Labels must start with a letter or underscore
    if (!isalpha(*token) && *token != '_') {
        return false;
    }

    // Labels can contain letters, digits, and underscores
    while (*token) {
        if (!isalnum(*token) && *token != '_') {
            return false;
        }
        token++;
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

    const char *directives[] = {".word", ".byte", ".half", ".float", ".double", ".space", ".ascii", ".asciiz", NULL};

    for (int i = 0; directives[i] != NULL; i++) {
        if (strcasecmp(token, directives[i]) == 0) {
            return true; // Valid directive found
        }
    }

    return false;

}
