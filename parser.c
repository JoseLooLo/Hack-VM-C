#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "parser.h"

void strip(char* line) {
    //
}

int is_commentary(char *line) {
    return line[0] == '/' && line[1] == '/';
}

int is_blankline(char*line) {
    for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++)
        if (line[i] != ' ')
            return 0;
    return 1;
}


int get_type(char* type) {
    if (!strcmp(type, "add")) {
        Type temp = C_ARITHMETIC;
        return temp;
    } else if (!strcmp(type, "sub")) {
        Type temp = C_ARITHMETIC;
        return temp;
    } else if (!strcmp(type, "neg")) {
        Type temp = C_ARITHMETIC;
        return temp;
    } else if (!strcmp(type, "eq")) {
        Type temp = C_ARITHMETIC;
        return temp;
    } else if (!strcmp(type, "gt")) {
        Type temp = C_ARITHMETIC;
        return temp;
    } else if (!strcmp(type, "lt")) {
        Type temp = C_ARITHMETIC;
        return temp;
    } else if (!strcmp(type, "and")) {
        Type temp = C_ARITHMETIC;
        return temp;
    } else if (!strcmp(type, "or")) {
        Type temp = C_ARITHMETIC;
        return temp; 
    } else if (!strcmp(type, "not")) {
        Type temp = C_ARITHMETIC;
        return temp;
    } else if (!strcmp(type, "push")) {
        Type temp = C_PUSH;
        return temp;
    } else if (!strcmp(type, "pop")) {
        Type temp = C_POP;
        return temp;
    } else {
        return -1;
    }
}

int get_type_str(char* line, char* type) {
    int i = 0;
    for (; line[i] != ' ' && line[i] != '\0' && line[i] != '\n'; i++)
        type[i] = line[i];
    type[i] = '\0';
    return i == 0;
}

int get_arg1_str(char* line, char* arg1) {
    int i = 0;
    for (; line[i] != ' '; i++) {
        if (line[i] == '\0' || line[i] == '\n')
            return 1; //This command has only one argumment
    }
    i++; //Skip the space
    int j = 0;
    for (j=0; line[i] != ' ' && line[i] != '\0' && line[i] != '\n'; i++, j++)
        arg1[j] = line[i];
    arg1[j] = '\0';
    return j == 0;
}

int get_arg2_str(char* line, char* arg2) {
    int i = 0;
    for (; line[i] != ' '; i++) {
        if (line[i] == '\0' || line[i] == '\n')
            return 1; //This command has only one argumment
    }
    i++; //Skip the space
    for (; line[i] != ' '; i++) {
        if (line[i] == '\0' || line[i] == '\n')
            return 1; //This command has only two argumment
    }
    i++; //Skip the second space
    int j = 0;
    for (j=0; line[i] != ' ' && line[i] != '\0' && line[i] != '\n'; i++, j++)
        arg2[j] = line[i];
    arg2[j] = '\0';
    return j == 0;
}

int check_memory_segment_str(char* segment) {
    if (!strcmp(segment, "local"))
        return 0;
    else if (!strcmp(segment, "constant"))
        return 0;
    else if (!strcmp(segment, "argument"))
        return 0;
    else if (!strcmp(segment, "pointer"))
        return 0;
    else if (!strcmp(segment, "this"))
        return 0;
    else if (!strcmp(segment, "that"))
        return 0;
    else if (!strcmp(segment, "static"))
        return 0;
    else if (!strcmp(segment, "temp"))
        return 0;
    else
        return 1;
}

int check_if_has_only_numbers(char* number) {
    int i = 0;
    for (; number[i] != '\0'; i++)
        if (number[i] < 48 || number[i] > 57)
            return 1;
    return i == 0;
}

int set_type(char* line, char* type, Command* cmd) {
    if (get_type_str(line, type) != 0)
        return 1;
    if ((cmd->command_type = get_type(type)) == -1)
        return 1;
    return 0;
}

int set_arg1(char* line, char* type, char* arg1, Command* cmd) {
    switch (cmd->command_type) {
        case C_ARITHMETIC:
            strcpy(cmd->arg1, type);
            return 0;
        case C_PUSH:
            if (get_arg1_str(line, arg1))
                return 1;
            if (check_memory_segment_str(arg1))
                return 1;
            strcpy(cmd->arg1, arg1);
            return 0;
        case C_POP:
            if (get_arg1_str(line, arg1))
                return 1;
            if (check_memory_segment_str(arg1))
                return 1;
            strcpy(cmd->arg1, arg1);
            return 0;
        default:
            return 1;
    }
}

int set_arg2(char* line, char* type, char* arg2, Command* cmd) {
    switch (cmd->command_type) {
        case C_ARITHMETIC:
            return 0;
        case C_PUSH:
            if (get_arg2_str(line, arg2))
                return 1;
            if (check_if_has_only_numbers(arg2))
                return 1;
            cmd->arg2 = atoi(arg2);
            return 0;
        case C_POP:
            if (get_arg2_str(line, arg2))
                return 1;
            if (check_if_has_only_numbers(arg2))
                return 1;
            cmd->arg2 = atoi(arg2);
            return 0;
        default:
            return 1;
    }
}

int check_command(char* line) {
    if (is_commentary(line))
        return 1;
    if (is_blankline(line))
        return 1;
    return 0;
}

void print_command(Command *cmd) {
    if (DEBUG_MODE) {
        switch (cmd->command_type) {
            case C_ARITHMETIC:
                printf("$ %s\n", cmd->arg1);
                break;
            case C_PUSH:
                printf("$ push %s %d\n", cmd->arg1, cmd->arg2);
                break;
            case C_POP:
                printf("$ push %s %d\n", cmd->arg1, cmd->arg2);
                break;
        }
    }
}

int create_command(char* line, Command *cmd) {
    char type[BUFFER_SIZE];
    char arg1[BUFFER_SIZE];
    char arg2[BUFFER_SIZE];

    strip(line); //@TODO
    
    if (check_command(line))
        return 1;
    
    if (set_type(line, type, cmd))
        return 2;

    if (set_arg1(line, type, arg1, cmd))
        return 3;

    if (set_arg2(line, type, arg2, cmd))
        return 4;

    print_command(cmd);
    return 0;
}
