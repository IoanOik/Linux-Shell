#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cmd.h"
#define A 256

int input_parsing(char user_input[], char *parse[]);
void exec_simple_command(char *parse[]);
void commands_with_ptrs(char *parse[], int arguments, char user_input[]);
void commands_with_pipes(char *parse[], int arguments, char user_input[]);

int main(int argc, char *argv[])
{
    char user_input[A];
    char *parse[A];
    int total_arguments, i;
    while (1)
    {
        printf("My shell>$ ");
        total_arguments = input_parsing(user_input, parse);
        if (strcmp(parse[0], "exit") == 0)
            break;
        commands_with_pipes(parse, total_arguments, user_input);
    }
    return 0;
}