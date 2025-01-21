#include "validator.h"

extern uint32_t current_data_address;
extern uint32_t current_text_address;
extern uint32_t program_counter;

// Validate and execute an instruction
void validate_inst(const char *instruction, char **operands, int operand_count) {

    InstructionInfo *inst_def = find_instruction(instruction);

    if (!inst_def) {
        printf("Error: Unknown instruction: %s\n", instruction);
        return;
    }

    // validate operands and store them in instruction
    if (!validate_operands(inst_def, operands, operand_count)) {
        printf("Operands are invalid for %s\n", inst_def->name);
        return;
    }

    // store instruction in Instruction array 
    extract_op(inst_def, operands, operand_count);

}

// could change strcmp to opcode validation instead, less expensive btw
// Validate operands based on instruction definition
bool validate_operands(const InstructionInfo *inst_def, char **operands, int operand_count) {

    // Check if the operand count matches
    if (inst_def->op_count != operand_count) {
        printf("Error: %s expects %d operands, found %d\n", inst_def->name, inst_def->op_count, operand_count);
        return false;
    }
    
    // Validate operands based on InstructionType
    switch (inst_def->type) {

        case R:

            //SLL
            if (strcmp(inst_def->name, "sll") && is_immediate(operands[2])) {
                for (int i = 0; i < operand_count - 1; i++) {
                    if (!is_register(operands[i])) {
                        printf("Error: Operand %d (%s) is not a valid register for instruction %s\n",
                            i + 1, operands[i], inst_def->name);
                        return false;
                    }
                }
            // mult
            } else if (strcmp(inst_def->name, "mult")) {

                if (!is_register(operands[0]) || !is_register(operands[1])) {
                    return false;
                }

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

        case J:

            if (!is_label(operands[0]) && !is_immediate(operands[0])) {
                return false;
            }

            if (is_label(operands[0]) && find_label_address(operands[0]) == -1) {
                return false;
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

bool extract_op(const InstructionInfo *inst_def, char **operands, int operand_count) {

    if (!validate_operands(inst_def, operands, operand_count)) {
        printf("Invalid instruction!\n");
        return false;
    }

    Instruction new_inst;
    new_inst.opcode = inst_def->opcode;
    new_inst.type = inst_def->type;

    switch (new_inst.type) {

        case R: 
            
            // standard values
            new_inst.value.RType.funct = inst_def->funct;
            new_inst.value.RType.shamt = 0;

            // sll
            if (new_inst.value.RType.funct == 0x00) {
                new_inst.value.RType.rd = get_register_index(operands[0]);
                new_inst.value.RType.rt = get_register_index(operands[1]);
                new_inst.value.RType.shamt = atoi(operands[2]);
            } else if (new_inst.value.RType.funct == 0x18) {    // mult
                new_inst.value.RType.rs = get_register_index(operands[0]);
                new_inst.value.RType.rt = get_register_index(operands[1]);
            } else {    // other cases
                new_inst.value.RType.rd = get_register_index(operands[0]);
                new_inst.value.RType.rs = get_register_index(operands[1]);
                new_inst.value.RType.rt = get_register_index(operands[2]);
            }

            break;

        case I:

            if (new_inst.opcode == 0x23 || new_inst.opcode == 0x2B) {
                new_inst.value.IType.rt = get_register_index(operands[0]);
                new_inst.value.IType.imm = extract_address(operands[1]);
                new_inst.value.IType.rs = extract_register(operands[1]);
            } else {
                new_inst.value.IType.rs = get_register_index(operands[0]);
                new_inst.value.IType.rt = get_register_index(operands[1]);
                new_inst.value.IType.imm = atoi(operands[2]);
            }

            break;

        case J:
            
            if (is_label(operands[0])) {
                new_inst.value.JType.address = find_label_address(operands[0]);
            } else {
                new_inst.value.JType.address = atoi(operands[0]);
            }
        
            break;

        case P:

            new_inst.value.PType.rt = get_register_index(operands[0]);

            if (is_label(operands[1])) {
                new_inst.value.PType.is_label = true;
                new_inst.value.PType.data.address = find_label_address(operands[1]);
            } else {
                new_inst.value.PType.is_label = false;
                new_inst.value.PType.data.imm = atoi(operands[1]);
            }

            break;

        case SYS:
            break;
        default:
            return false;
    }   

    store_instruction_to_memory(current_text_address, new_inst);
    current_text_address++;

    return true;

}

int extract_register(const char *operand) {

    if (operand == NULL) {
        return -1;
    }

    char *open_paren = strchr(operand, '(');
    char *closed_paren = strchr(operand, ')');

    if (open_paren == NULL || closed_paren == NULL) {
        return -1;
    }

    // Extract the register name inside parentheses
    size_t reg_len = closed_paren - open_paren - 1;
    if (reg_len <= 0 || reg_len >= 8) { // Assuming max register name length is 7
        return -1;
    }

    char reg[8];
    strncpy(reg, open_paren + 1, reg_len);
    reg[reg_len] = '\0';

    return get_register_index(reg);

}

int extract_address(const char *operand) {

    if (operand == NULL) {
        return -1;
    }

    char *open_paren = strchr(operand, '(');
    char *closed_paren = strchr(operand, ')');

    if (open_paren == NULL || closed_paren == NULL) {
        return -1;
    }

    // Extract the register name inside parentheses
    size_t reg_len = closed_paren - open_paren - 1;
    if (reg_len <= 0 || reg_len >= 8) { // Assuming max register name length is 7
        return -1;
    }

    char reg[8];
    strncpy(reg, open_paren + 1, reg_len);
    reg[reg_len] = '\0';

    // Check the offset part
    size_t offset_len = open_paren - operand;
    if (offset_len <= 0 || offset_len >= 16) { // Assuming max offset length
        return -1;
    }

    char offset_str[16];
    strncpy(offset_str, operand, offset_len);
    offset_str[offset_len] = '\0';

    // Validate offset is a number
    char *endptr;

    return strtol(offset_str, &endptr, 10);

}

// Validate and handle data directives
void validate_data_field(const char *label_name, char **args, int arg_count, Label *label_arr) {

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

             // If it's the first word and label_name is provided, map the label to this address
            if (i == 1 && label_name != NULL) {
                add_label(label_name, current_data_address);
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

        add_label(label_name, current_data_address);
        
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
