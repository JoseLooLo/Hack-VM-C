#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "codewriter.h"

void write_increment_stack(FILE* file) {
    char *increment_stack = "@SP\nM=M+1\n";
    fprintf(file, increment_stack);
}

void write_decrement_stack(FILE* file) {
    char *decrement_stack = "@SP\nM=M-1\n";
    fprintf(file, decrement_stack);
}

void write_constant_string(FILE* file, int cns) {
    fprintf(file, "@%d\n", cns);
}

void write_temp_adress(FILE* file, int offset) {
    int temp = 5 + offset;
    fprintf(file, "@%d\n", temp);
}

void write_static_adress(FILE* file, int arg2, char* filename) {
    fprintf(file, "@%s.%d\n", filename, arg2);
}

void write_segment_adress(FILE* file, char* segment) {
    if (!strcmp(segment, "local")) {
        fprintf(file, "@LCL\n");
    } else if (!strcmp(segment, "argument")) {
        fprintf(file, "@ARG\n");
    } else if (!strcmp(segment, "this")) {
        fprintf(file, "@THIS\n");
    } else if (!strcmp(segment, "that")) {
        fprintf(file, "@THAT\n");
    }
}

//Labels

void write_equals_label(FILE* file, int n) {
    fprintf(file, "@EQ%d\n", n);
}

void write_equals_label_jump(FILE* file, int n) {
    fprintf(file, "(EQ%d)\n", n);
}

void write_gt_label(FILE* file, int n) {
    fprintf(file, "@GT%d\n", n);
}

void write_gt_label_jump(FILE* file, int n) {
    fprintf(file, "(GT%d)\n", n);
}

void write_lt_label(FILE* file, int n) {
    fprintf(file, "@LT%d\n", n);
}

void write_lt_label_jump(FILE* file, int n) {
    fprintf(file, "(LT%d)\n", n);
}

void write_end_label(FILE* file, int n) {
    fprintf(file, "@END%d\n", n);
}

void write_end_label_jump(FILE* file, int n) {
    fprintf(file, "(END%d)\n", n);
}

//


void write_add(FILE* file) {
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "D=M\n");
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "A=M\n");
    fprintf(file, "D=A+D\n");
    fprintf(file, "@SP\n");
    fprintf(file, "A=M\n");
    fprintf(file, "M=D\n");
    write_increment_stack(file);
}

void write_sub(FILE* file) {
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "D=M\n");
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "A=M\n");
    fprintf(file, "D=A-D\n");
    fprintf(file, "@SP\n");
    fprintf(file, "A=M\n");
    fprintf(file, "M=D\n");
    write_increment_stack(file);
}

void write_neg(FILE* file) {
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "D=M\n");
    fprintf(file, "D=-D\n");
    fprintf(file, "@SP\n");
    fprintf(file, "A=M\n");
    fprintf(file, "M=D\n");
    write_increment_stack(file);
}

void write_and(FILE* file) {
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "D=M\n");
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "D=M&D\n");
    fprintf(file, "@SP\n");
    fprintf(file, "A=M\n");
    fprintf(file, "M=D\n");
    write_increment_stack(file);
}

void write_or(FILE* file) {
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "D=M\n");
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "D=M|D\n");
    fprintf(file, "@SP\n");
    fprintf(file, "A=M\n");
    fprintf(file, "M=D\n");
    write_increment_stack(file);
}

void write_not(FILE* file) {
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "D=M\n");
    fprintf(file, "D=!D\n");
    fprintf(file, "@SP\n");
    fprintf(file, "A=M\n");
    fprintf(file, "M=D\n");
    write_increment_stack(file);
}

void write_eq(FILE* file, int n) {
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "D=M\n");
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "A=M\n");
    fprintf(file, "D=A-D\n");
    write_equals_label(file, n);
    fprintf(file, "D;JEQ\n");
    //
    write_constant_string(file, 0);
    fprintf(file, "D=A\n");
    write_end_label(file, n);
    fprintf(file, "D;JMP\n");
    //
    write_equals_label_jump(file, n);
    write_constant_string(file, 0);
    fprintf(file, "D=A\n");
    fprintf(file, "D=D-1\n");
    write_end_label_jump(file, n);
    fprintf(file, "@SP\n");
    fprintf(file, "A=M\n");
    fprintf(file, "M=D\n");
    write_increment_stack(file);
}

void write_gt(FILE* file, int n) {
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "D=M\n");
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "A=M\n");
    fprintf(file, "D=A-D\n");
    write_gt_label(file, n);
    fprintf(file, "D;JGT\n");
    //
    write_constant_string(file, 0);
    fprintf(file, "D=A\n");
    write_end_label(file, n);
    fprintf(file, "D;JMP\n");
    //
    write_gt_label_jump(file, n);
    write_constant_string(file, 0);
    fprintf(file, "D=A\n");
    fprintf(file, "D=D-1\n");
    write_end_label_jump(file, n);
    fprintf(file, "@SP\n");
    fprintf(file, "A=M\n");
    fprintf(file, "M=D\n");
    write_increment_stack(file);
}

void write_lt(FILE* file, int n) {
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "D=M\n");
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "A=M\n");
    fprintf(file, "D=A-D\n");
    write_lt_label(file, n);
    fprintf(file, "D;JLT\n");
    //
    write_constant_string(file, 0);
    fprintf(file, "D=A\n");
    write_end_label(file, n);
    fprintf(file, "D;JMP\n");
    //
    write_lt_label_jump(file, n);
    write_constant_string(file, 0);
    fprintf(file, "D=A\n");
    fprintf(file, "D=D-1\n");
    write_end_label_jump(file, n);
    fprintf(file, "@SP\n");
    fprintf(file, "A=M\n");
    fprintf(file, "M=D\n");
    write_increment_stack(file);
}

void write_push_constant(FILE* file, int arg2) {
    write_constant_string(file, arg2);
    fprintf(file, "D=A\n");
    fprintf(file, "@SP\n");
    fprintf(file, "A=M\n");
    fprintf(file, "M=D\n");
    write_increment_stack(file);
}

void write_push_temp(FILE* file, int arg2) {
    write_temp_adress(file, arg2);
    fprintf(file, "D=M\n");
    fprintf(file, "@SP\n");
    fprintf(file, "A=M\n");
    fprintf(file, "M=D\n");
    write_increment_stack(file);
}

void write_push_static(FILE* file, int arg2, char* filename) {
    write_static_adress(file, arg2, filename);
    fprintf(file, "D=M\n");
    fprintf(file, "@SP\n");
    fprintf(file, "A=M\n");
    fprintf(file, "M=D\n");
    write_increment_stack(file);
}

void write_push_pointer(FILE* file, int arg2) {
    if (arg2 == 0) {
        write_segment_adress(file, "this");
        fprintf(file, "D=M\n");
        fprintf(file, "@SP\n");
        fprintf(file, "A=M\n");
        fprintf(file, "M=D\n");
        write_increment_stack(file);
    } else if (arg2 == 1) {
        write_segment_adress(file, "that");
        fprintf(file, "D=M\n");
        fprintf(file, "@SP\n");
        fprintf(file, "A=M\n");
        fprintf(file, "M=D\n");
        write_increment_stack(file);
    } else {
        fprintf(file, "//++++++++++++++++++++++++++++++++\n");
        fprintf(file, "//Invalid value for pointer adress\n");
        fprintf(file, "//++++++++++++++++++++++++++++++++\n");
    }
}

void write_push_generic(FILE* file, char* arg1, int arg2) {
    write_constant_string(file, arg2);
    fprintf(file, "D=A\n");
    write_segment_adress(file, arg1);
    fprintf(file, "A=M\n");
    fprintf(file, "A=D+A\n");
    fprintf(file, "D=M\n");
    fprintf(file, "@SP\n");
    fprintf(file, "A=M\n");
    fprintf(file, "M=D\n");
    write_increment_stack(file);
}

void write_pop_temp(FILE* file, int arg2) {
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "D=M\n");
    write_temp_adress(file, arg2);
    fprintf(file, "M=D\n");
}

void write_pop_static(FILE* file, int arg2, char* filename) {
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "D=M\n");
    write_static_adress(file, arg2, filename);
    fprintf(file, "M=D\n");
}

void write_pop_pointer(FILE* file, int arg2) {
    if (arg2 == 0) {
        write_decrement_stack(file);
        fprintf(file, "@SP\n");
        fprintf(file, "A=M\n");
        fprintf(file, "D=M\n");
        write_segment_adress(file, "this");
        fprintf(file, "M=D\n");
    } else if (arg2 == 1) {
        write_decrement_stack(file);
        fprintf(file, "@SP\n");
        fprintf(file, "A=M\n");
        fprintf(file, "D=M\n");
        write_segment_adress(file, "that");
        fprintf(file, "M=D\n");
    } else {
        fprintf(file, "//++++++++++++++++++++++++++++++++\n");
        fprintf(file, "//Invalid value for pointer adress\n");
        fprintf(file, "//++++++++++++++++++++++++++++++++\n");
    }
}

void write_pop_generic(FILE* file, char* arg1, int arg2) {
    write_constant_string(file, arg2);
    fprintf(file, "D=A\n");
    write_segment_adress(file, arg1);
    fprintf(file, "A=M\n");
    fprintf(file, "D=A+D\n");
    write_temp_adress(file, 0);
    fprintf(file, "M=D\n");
    write_decrement_stack(file);
    fprintf(file, "A=M\n");
    fprintf(file, "D=M\n");
    write_temp_adress(file, 0);
    fprintf(file, "A=M\n");
    fprintf(file, "M=D\n");
}

void write_pop(FILE* file, char* arg1, int arg2, char* filename) {
    if (!strcmp(arg1, "temp")) {
        write_pop_temp(file, arg2);
    } else if (!strcmp(arg1, "static")) {
        write_pop_static(file, arg2, filename);
    } else if (!strcmp(arg1, "pointer")) {
        write_pop_pointer(file, arg2);
    } else {
        write_pop_generic(file, arg1, arg2);
    }
}

void write_push(FILE* file, char* arg1, int arg2, char* filename) {
    if (!strcmp(arg1, "constant")) {
        write_push_constant(file, arg2);
    } else if (!strcmp(arg1, "temp")) {
        write_push_temp(file, arg2);
    } else if (!strcmp(arg1, "static")) {
        write_push_static(file, arg2, filename);
    } else if (!strcmp(arg1, "pointer")) {
        write_push_pointer(file, arg2);
    } else {
        write_push_generic(file, arg1, arg2);
    }
}

void write_arithmetic(FILE* file, char* arg1, int n) {
    if (!strcmp(arg1, "add")) {
        write_add(file);
    } else if (!strcmp(arg1, "sub")) {
        write_sub(file);
    } else if (!strcmp(arg1, "neg")) {
        write_neg(file);
    } else if (!strcmp(arg1, "eq")) {
        write_eq(file, n);
    } else if (!strcmp(arg1, "gt")) {
        write_gt(file, n);
    } else if (!strcmp(arg1, "lt")) {
        write_lt(file, n);
    } else if (!strcmp(arg1, "and")) {
        write_and(file);
    } else if (!strcmp(arg1, "or")) {
        write_or(file);
    } else if (!strcmp(arg1, "not")) {
        write_not(file);
    }
}

void write_command(FILE* file, Command *cmd, char* filename, int n) {
    switch (cmd->command_type) {
        case C_ARITHMETIC:
            fprintf(file, "//%s\n", cmd->arg1);
            write_arithmetic(file, cmd->arg1, n);
            break;
        case C_PUSH:
            fprintf(file, "//push %s %d\n", cmd->arg1, cmd->arg2);
            write_push(file, cmd->arg1, cmd->arg2, filename);
            break;
        case C_POP:
            fprintf(file, "//push %s %d\n", cmd->arg1, cmd->arg2);
            write_pop(file, cmd->arg1, cmd->arg2, filename);
            break;
        
        default:
            break;
    }
}