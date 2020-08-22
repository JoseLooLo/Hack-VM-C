#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "codewriter.h"
#include "parser.h"

void get_name_new_file(char* name, char* new) {
    int i = 0;
    for (; name[i] != '\0' && name[i] != '.'; i++)
        new[i] = name[i];
    new[i] = '\0';
    strcat(new, ".asm");
    if (DEBUG_MODE) {
        printf("# New file name %s\n", new);
    }
}

int read_file(char* name) {
    FILE* fptr = fopen(name, "r");
    if (fptr == NULL){
        printf("Failed to load the file %s\n", name);
        return 1;
    }
    
    char new_name[BUFFER_SIZE];
    get_name_new_file(name, new_name);
    FILE* fptr_n = fopen(new_name, "w");
    if (fptr_n == NULL) {
        printf("Failed to create the file %s\n", new_name);
        return 1;
    }

    printf("Reading file %s...\n", name);
    char buffer[BUFFER_SIZE];
    int line_counter = 0;
    while (fgets(buffer, sizeof(buffer), fptr) != NULL ){
        line_counter++;
        Command cmd;
        int res = create_command(buffer, &cmd);
        switch (res) {
            case 0:
                write_command(fptr_n, &cmd, new_name, line_counter);
                break;
            case 1:
                if (DEBUG_MODE) {
                    printf("& Comentary or blankline at the line [%d]\n", line_counter);
                }
                continue;
            case 2:
                if (DEBUG_MODE) {
                    printf("& Invalid type at the line [%d]\n", line_counter);
                }
                continue;
            case 3:
                if (DEBUG_MODE) {
                    printf("& Invalid arg1 at the line [%d]\n", line_counter);
                }
                continue;
            case 4:
                if (DEBUG_MODE) {
                    printf("& Invalid arg2 at the line [%d]\n", line_counter);
                }
                continue;
            
            default:
                printf("Invalid command -> %s", buffer);
                exit(1);
                break;
        }
    }

    //Close open files
    fclose(fptr);
    fclose(fptr_n);
    return 0;
}

int main(int argc, char** argv) {
    for (int i = 1; i < argc; i++)
        read_file(argv[i]);

    return 0;
}