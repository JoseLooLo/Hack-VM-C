#ifndef COMMANDS_H
#define COMMANDS_H

#define BUFFER_SIZE 255
#define DEBUG_MODE 1

typedef enum Type {
    C_ARITHMETIC = 1,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL
} Type;

typedef struct Command {
    Type command_type;
    char arg1[BUFFER_SIZE];
    int arg2;
} Command;

#endif