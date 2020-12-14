#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#ifndef MAX_LEN
#define MAX_LEN 256
#endif

#ifndef INSTRUCTION_NUM
#define INSTRUCTION_NUM 21
#endif

#ifndef WORD
#define WORD 4
#endif

/*******************************************************
 * Function Declaration
 *******************************************************/
void process(FILE *input, FILE *output);
void initialize_instruction_table(void);
int get_text_section_location(FILE *input);
int resolve_data_section(FILE *input, int text_section_location);
void resolve_text_section_labels(FILE *input, int text_section_location);
void diassemble_instructions(FILE *input, int text_section_location);
int diassemble_pseudo_instructions(void);
void convert_instructions_to_binary(FILE *output);
void convert_data_to_binary(FILE *output, int data_section_size);
void convert_section_size_to_binary(FILE *output, int data_section_size, int text_section_size);
char *change_file_ext(char *str);
void convert_decimal_to_binary(char *bin, int dec, int max_bit);

/*******************************************************
 * Global Declaration
 ******************************************************/
typedef enum { false, true } bool;

typedef struct {
    char name[MAX_LEN];
    int pointer;
    int sequence[3];
    int opcode;
    int funct;
    bool is_occupied;
} INSTRUCTION_TABLE;

typedef struct {
    char name[MAX_LEN];
    int value;
    int address;
} DATA;

typedef struct {
    int next;
    char instruction[MAX_LEN];
    int opcode;
    int funct;
    int address;
    int arguments[4];
    bool is_label;
} TEXT;

typedef struct {
    char name[MAX_LEN];
    int address;
    int new_address;
} LABEL;

INSTRUCTION_TABLE instruction_table[MAX_LEN];
DATA data[MAX_LEN];
TEXT text[MAX_LEN];
LABEL labels[MAX_LEN];

/*******************************************************
 * Function: main
 *
 * Parameters:
 *  int
 *      argc: the number of argument
 *  char*
 *      argv[]: array of a sting argument
 *
 * Return:
 *  return success exit value
 *
 * Info:
 *  The typical main function in C language.
 *  It reads system arguments from terminal (or commands)
 *  and parse an assembly file(*.s).
 *  Then, it converts a certain instruction into
 *  object code which is basically binary code.
 *******************************************************/
int
main(int argc, char *argv[])
{
    FILE *input, *output;
    char *filename;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <*.s>\n", argv[0]);
        fprintf(stderr, "Example: %s sample_input/example?.s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    input = fopen(argv[1], "r");
    if (input == NULL) {
        perror("ERROR");
        exit(EXIT_FAILURE);
    }

    filename = strdup(argv[1]); // strdup() is not a standard C library but fairy used a lot.
    if(change_file_ext(filename) == NULL) {
        fprintf(stderr, "'%s' file is not an assembly file.\n", filename);
        exit(EXIT_FAILURE);
    }

    output = fopen(filename, "w");
    if (output == NULL) {
        perror("ERROR");
        exit(EXIT_FAILURE);
    }

    process(input, output);

    fclose(input);
    fclose(output);
    exit(EXIT_SUCCESS);
}

/*******************************************************
 * Function: process
 *
 * Parameters:
 *  FILE*
 *      input: an assembly file (*.s)
 *      output: an object file (*.o)
 *
 * Info:
 *  This function converts assembly code to machine code.
 *  It works as the core of this codes.
 *****************************************************/
void
process(FILE *input, FILE *output)
{
    int data_section_size = 0;
    int text_section_size = 0;
    int text_section_location = 0;

    initialize_instruction_table();

    text_section_location = get_text_section_location(input);
 
    data_section_size = (resolve_data_section(input, text_section_location) - 1) * WORD;
    resolve_text_section_labels(input, text_section_location); 
    diassemble_instructions(input, text_section_location);
    text_section_size = diassemble_pseudo_instructions() * WORD;

    convert_section_size_to_binary(output, data_section_size, text_section_size);
    convert_instructions_to_binary(output);
    convert_data_to_binary(output, data_section_size);    
    
    fputc('\n', output);
}

int
diassemble_pseudo_instructions(void) {
    int id = 0;
    int origin_id = 0;
    int origin_arguments[4];
    int text_len = 0;
    int current_address = 0;
    int offset = 0;
    int base = 0;
    int i = 0;

    while (text[text_len].next != -1) {
        text_len += 1;
    }

    while (text[id + 1].next != -1) {
       if (offset > 0) {
           text[id].address = current_address + offset * 4;
       }

       current_address = text[id].address;

       if (text[id].opcode == -1) { // la instruction 
           if (offset == 0) {
               base = current_address;
           }

           origin_arguments[0] = text[id].arguments[0];
           origin_arguments[1] = text[id].arguments[1];

           strncpy(text[id].instruction, "lui", 4);
           text[id].opcode = 0xf; // add lui instruction
           text[id].address = current_address;
           
           text[id].arguments[0] = 0;
           text[id].arguments[1] = origin_arguments[0];
           text[id].arguments[2] = origin_arguments[1] >> 16;

           if ((origin_arguments[1] << 16) > 0) { // add ori instruction
               text_len += 1;
               offset += 1;
               
               strncpy(text[text_len].instruction, "ori", 4);
               text[text_len].opcode = 0xd;
               text[text_len].address = current_address;

               text[text_len].arguments[0] = text[id].arguments[1];
               text[text_len].arguments[1] = text[id].arguments[1];
               text[text_len].arguments[2] = origin_arguments[1] - 0x10000000;
               
               text[id].next = text_len;
               text[text_len].next = id + 1; 
           }
       }

        id = text[id].next;
    }

    for (i = 0; labels[i].address != -1; i += 1) {
        if (labels[i].address > base) {
            labels[i].new_address = labels[i].address + offset * 4;
        } else {
            labels[i].new_address = labels[i].address;
        }
    }

    id = 0;
     
    while (text[id + 1].next != -1) {
        if (text[id].is_label) {
            for (i = 0; i < MAX_LEN; i += 1) {
                if (text[id].arguments[2] == labels[i].address) {   
                    text[id].arguments[2] = labels[i].new_address;
                    labels[i].address = labels[i].new_address;
                    break;
                } else if (text[id].arguments[0] == labels[i].address) {
                    text[id].arguments[0] = labels[i].new_address;
                    labels[i].address = labels[i].new_address;
                    break;
                }
            }
        }
        id = text[id].next;
    }

    return text_len - 1;
}

void
convert_instructions_to_binary(FILE *output) {
    char binary[33];
    char temp_bin[33];
    int value = 0;
    int id = 0;
    int i = 0;

    while (text[id + 1].next != -1) {
        if (text[id].opcode == 0) { // R-format
            convert_decimal_to_binary(temp_bin, text[id].opcode, 6);
            strncat(binary, temp_bin, strlen(temp_bin));
            
            for (i = 0; i < 4; i += 1) {
                convert_decimal_to_binary(temp_bin, text[id].arguments[i], 5);
                strncat(binary, temp_bin, strlen(temp_bin));
            }
           
            convert_decimal_to_binary(temp_bin, text[id].funct, 6);
            strncat(binary, temp_bin, strlen(temp_bin));
        } else if (text[id].opcode == 0x2 || text[id].opcode == 0x3) { // J-format 
            convert_decimal_to_binary(temp_bin, text[id].opcode, 6);
            strncat(binary, temp_bin, strlen(temp_bin));

            convert_decimal_to_binary(temp_bin, text[id].arguments[0] >> 2, 26);
            strncat(binary, temp_bin, strlen(temp_bin));
        } else { // I-format
            convert_decimal_to_binary(temp_bin, text[id].opcode, 6);
            strncat(binary, temp_bin, strlen(temp_bin));
            
            convert_decimal_to_binary(temp_bin, text[id].arguments[0], 5);
            strncat(binary, temp_bin, strlen(temp_bin));
            
            convert_decimal_to_binary(temp_bin, text[id].arguments[1], 5);
            strncat(binary, temp_bin, strlen(temp_bin));

            if (text[id].is_label) {
                convert_decimal_to_binary(temp_bin, (text[id].arguments[2] - (text[id].address + WORD)) / WORD, 16);
            } else {
                convert_decimal_to_binary(temp_bin, text[id].arguments[2], 16);
            }

            strncat(binary, temp_bin, strlen(temp_bin));    
        }
       
        fprintf(output, "%s", binary);
        strncpy(binary, "", 1);
        id = text[id].next;
    }
}

void
convert_data_to_binary(FILE *output, int data_section_size) {
    char binary[33];
    int i;
    
    if (data_section_size) {
        for (i = 1; i <= data_section_size / WORD; i += 1) {
            convert_decimal_to_binary(binary, data[i].value, 32);
            fprintf(output, "%s", binary);
        }
    }
}

void
convert_section_size_to_binary(FILE *output, int data_section_size, int text_section_size) {
    char binary[33];

    rewind(output);

    convert_decimal_to_binary(binary, text_section_size, 32);
    fprintf(output, "%s", binary);

    convert_decimal_to_binary(binary, data_section_size, 32);
    fprintf(output, "%s", binary);
}

/*******************************************************
 * Function: initializ_instruction_table
 *
 * Info:
 *  This function initializes the instruction table.
 *****************************************************/
void
initialize_instruction_table(void) {
    char instructions[INSTRUCTION_NUM][MAX_LEN] = {
        "addiu", "addu", "and", "andi", "beq",
        "bne", "j", "jal", "jr", "lui",
        "lw", "la", "nor", "or", "ori",
        "sltiu", "sltu", "sll", "srl", "sw",
        "subu"
    };
    int opcodes[INSTRUCTION_NUM] = {
        0x9, 0x0, 0x0, 0xc, 0x4,
        0x5, 0x2, 0x3, 0, 0xf,
        0x23, -1, 0, 0, 0xd,
        0xb, 0, 0, 0, 0x2b,
        0
    };
    int functs[INSTRUCTION_NUM] = {
        -1, 0x21, 0x24, -1, -1,
        -1, -1, -1, 0x8, -1,
        -1, -1, 0x27, 0x25, -1,
        -1, 0x2b, 0x0, 0x2, -1,
        0x23,
    };
    int sequence[INSTRUCTION_NUM][3] = { // rs, rt, rd
        {1, 0, 2}, // addiu
        {2, 0, 1}, // addu
        {2, 0, 1}, // and
        {1, 0, 2}, // andi
        {0, 1, 2}, // beq
        {0, 1, 2}, // bne
        {0, -1, -1}, // j
        {0, -1, -1}, // jal
        {0, -1, -1}, // jr
        {1, 2, -1}, // lui
        {1, 0, 2}, // lw
        {0, 1, -1}, // la
        {2, 0, 1}, // nor
        {2, 0, 1}, // or
        {1, 0, 2}, // ori
        {1, 0, 2}, // sltiu
        {2, 0, 1}, // sltu
        {2, 1, 3}, // sll
        {2, 1, 3}, // srl
        {1, 2, 1}, // sw
        {2, 0, 1} // subu
    };
    int id = 0;
    int i, j;

    for (i = 0; i < INSTRUCTION_NUM; i += 1) {
        id = instructions[i][0] - 96 + instructions[i][strlen(instructions[i]) - 1] - 96;

        for (j = id; instruction_table[j].is_occupied == 1; j += 1) {
            instruction_table[id].pointer = id + 1;
            id += 1;
        }
        
        strncpy(instruction_table[id].name, instructions[i], strlen(instructions[i]));
        instruction_table[id].is_occupied = 1;
        instruction_table[id].opcode = opcodes[i];
        instruction_table[id].funct = functs[i];
        
        for (j = 0; sequence[i][j] != -1 && j < 3; j += 1) {
            instruction_table[id].sequence[j] = sequence[i][j];
        }
    }
}

/*******************************************************
 * Function: diassemble_instructions
 *
 * Parameters:
 *  FILE*
 *      input: an assembly file (*.s)
 *  int
 *      text_sections_location: the start point of text section
 *
 * Info:
 *  This function disassembles instructions in the input
 *  file. It resolves instruction name, opcode, funct,
 *  and arguments.
 *****************************************************/
void
diassemble_instructions(FILE *input, int text_section_location) {
    int index = 0;
    int id = 0;
    int current_address = 0x400000;
    int seq_index = 0;
    int arg_index = 0;
    int arg_value = 0;
    char line[MAX_LEN];
    char prefix, postfix;
    char *token;
    char *temp;
    int i;

    fseek(input, text_section_location, SEEK_SET);

    while (!feof(input)) {
        fgets(line, MAX_LEN, input);
        token = strtok(line, "\t");
        
        postfix = token[strlen(token) - 2];

        if (postfix != ':') {
            do {
                prefix = token[0];
                postfix = token[strlen(token) - 1];
               
                if (isalpha(prefix) && postfix != ',' && token[strlen(token) - 1] != '\n') { // name
                    id = prefix - 96 + postfix - 96;
                    token[strlen(token)] = '\0';
                    
                    while (strcmp(instruction_table[id].name, token)) {
                        id = instruction_table[id].pointer;
                    }
                    
                    strncpy(text[index].instruction, token, strlen(token));
                    text[index].address = current_address;
                    text[index].opcode = instruction_table[id].opcode;
                    text[index].funct = instruction_table[id].funct;
                } else if (prefix == '$') { // register
                    token[0] = '0';
                    arg_index = instruction_table[id].sequence[seq_index];
                    text[index].arguments[arg_index] = atoi(token);
                    seq_index += 1;
                } else if (isalpha(prefix)) { // label or data
                    strncpy(temp, token, strlen(token));
                    temp[strlen(token) - 1] = '\0';
                    arg_index = instruction_table[id].sequence[seq_index];
                    
                    for (i = 0; i < MAX_LEN; i += 1) {
                        if (!strcmp(labels[i].name, temp)) {    
                            text[index].arguments[arg_index] = labels[i].address;
                            text[index].is_label = 1;
                            break;
                        } else if (!strcmp(data[i].name, temp)) {
                            text[index].arguments[arg_index] = data[i].address;
                            text[index].is_label = 0;
                            break;
                        }
                    }

                    seq_index += 1;
                } else if (token[strlen(token) - 2] == ')') {
                    static char base[MAX_LEN];
                    static char offset[MAX_LEN];
                    int offset_num = 0, base_num = 0;
                    int base_idx = 0, offset_idx = 0;
                    bool is_neg = 0;
                    bool is_outside = 1;

                    for (i = 0; token[i] != ')'; i += 1) {
                        if (is_outside && token[i] == '-') {
                            is_neg = 1;
                        }

                        if (token[i] == '(') {
                            is_outside = 0;
                        }

                        if (!is_outside && isdigit(token[i])) {
                            base[base_idx] = token[i];
                            base_idx += 1;
                            base[base_idx] = '\0';
                        } else if (is_outside && isdigit(token[i])) {
                            offset[offset_idx] = token[i];
                            offset_idx += 1;
                            offset[offset_idx] = '\0';
                        }
                    }
                    
                    offset_num = atoi(offset);
                    base_num = atoi(base);
                    
                    if (is_neg) {
                        offset_num = offset_num * -1;
                    }
                    
                    if (!strncmp(text[index].instruction, "lw", 3)) {
                        text[index].arguments[0] = base_num;
                        text[index].arguments[2] = offset_num;
                    } else {
                        text[index].arguments[2] = offset_num;
                        text[index].arguments[0] = base_num;
                    }

                    strncpy(base, "", 1);
                    strncpy(offset, "", 1);
                } else if (isxdigit(prefix)) { // number
                    arg_index = instruction_table[id].sequence[seq_index];
                    text[index].arguments[arg_index] = (int)strtol(token, NULL, 0);
                    seq_index += 1;
                }
            } while (token = strtok(NULL, " ")); 
        
            current_address += 4;
            text[index].next = index + 1;
            index += 1;
        }

        seq_index = 0;
    }

    text[index].next = -1;
}

/******************************************************
 * Function: get_text_section_location
 *
 * Parameters:
 *  FILE*
 *      input: an assembly file
 *
 * Return:
 *  return the start point of text section from top of the file
 *
 * Info: 
 *  This function finds the start point of text section.
 *****************************************************/
int
get_text_section_location(FILE *input) {
    int text_section_location = 0;
    char line[MAX_LEN]; 

    rewind(input);

    while (strcmp("\t.text\n", line)) {
        fgets(line, MAX_LEN, input);
    }

    text_section_location = ftell(input);
    rewind(input);

    return text_section_location;
}

/******************************************************
 * Function: resolve_data_section
 *
 * Parameters:
 *  FILE*
 *      input: an assembly file
 *  int
 *      text_section_location: the start point of text section
 *
 * Return:
 *  return the number of the data
 *
 * Info: 
 *  This function reads lines of the text section for
 *  resolving and storing the data.
 *****************************************************/
int
resolve_data_section(FILE *input, int text_section_location)
{
    int current_address = 0xffffffc; // 0x1000 0000 - 4
    int index = 0;
    char line[MAX_LEN];
    char prefix, postfix;
    char *token;

    while (ftell(input) != text_section_location) {
        fgets(line, MAX_LEN, input);
        token = strtok(line, "\t");
       
        do {
            prefix = token[0];
            postfix = token[strlen(token) - 1];

            if (postfix == ':') {
                token[strlen(token) - 1] = '\0';
                strncpy(data[index].name, token, MAX_LEN);
            } else if (prefix != '.' && strtol(token, NULL, 0)) {
                data[index].value = (int)strtol(token, NULL, 0);
                data[index].address = current_address;
            }
        } while (token = strtok(NULL, "\t"));

        current_address += 4;
        index += 1;
    }

    return index - 1;
}

/******************************************************
 * Function: resolve_text_section_labels
 *
 * Parameters:
 *  FILE*
 *      input: an assembly file
 *  int
 *      text_section_location: the start point of text section
 *
 * Info: 
 *  This function resolves the labels in text section,
 *  and stores it.
 *****************************************************/
void
resolve_text_section_labels(FILE *input, int text_section_location) {
    int current_address = 0x400000;
    int index = 0;
    char line[MAX_LEN];
    char postfix;
    char *token;

    fseek(input, text_section_location, SEEK_SET);

    while (!feof(input)) {
        fgets(line, MAX_LEN, input);
        token = strtok(line, "\t");
        postfix = token[strlen(token) - 2];

        if (postfix == ':') {
            token[strlen(token) - 2] = '\0';

            strncpy(labels[index].name, token, MAX_LEN);
            labels[index].address = current_address;

            index += 1;
        } else {
            current_address += WORD;
        }
    }

    labels[index].address = -1;
}

/*******************************************************
 * Function: change_file_ext
 *
 * Parameters:
 *  char*
 *      str: a raw filename (without path)
 *
 * Return:
 *  return NULL if a file is not an assembly file.
 *  return empty string
 *
 * Info:
 *  This function reads filename and converst it into
 *  object extention name, *.o
 *******************************************************/
char
*change_file_ext(char *str)
{
    char *dot = strrchr(str, '.');

    if (!dot || dot == str || (strcmp(dot, ".s") != 0)) {
        return NULL;
    }

    str[strlen(str) - 1] = 'o';
    return "";
}

/*******************************************************
 * Function: convert_decimal_to_binary
 *
 * Parameters:
 *  char*
 *      bin: a binary string will save result
 *  int
 *      dec: a decimal number
 *      max_bit: a maximum size of the binary number
 *
 * Info:
 *  This function converts decimal number to binary bits,
 *  and saves it to string.
 *******************************************************/
void
convert_decimal_to_binary(char *bin, int dec, int max_bit)
{
    int i = max_bit - 1;
    int identifier = 0;
    char *result;

    result = (char*)malloc(sizeof(char) * (max_bit + 1));
    
    for (i; i >= 0; i--) {
        identifier = dec >> i;
        
        if (identifier & 1) {
            result[max_bit - 1 - i] = '1';
        } else {
            result[max_bit -1 - i] = '0';
        }
    }

    result[max_bit] = '\0';
    strncpy(bin, result, max_bit + 1);

    free(result);
}
