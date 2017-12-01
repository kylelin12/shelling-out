#include "bash_shell.h"

int bash_shell() {
    
    // Runs the rd_line() function to return a string containing the input from stdin
    char *inputcmd = rd_line();

    // Parses the input command into tokens that represent the arguments
    char **commands = parseargs(inputcmd);

    // Executes commands that don't work in a forked process
    cnt_fork(commands);

    // Execute the commands from a forked process
    exec_commands(commands);

    return 0;
}

// Runs 
void cnt_fork(char **commands) {
    // Exceptions for cd and exit
    if (strcmp(commands[0], "cd") == 0) {
        chdir(commands[1]);
    } else if (strcmp(commands[0], "exit") == 0) {
        exit(0);
    }
}

// Returns a string containing the input from stdin
char *rd_line() {
    // Stores the input taken from stdin to a character pointer
    char *inputcmd = malloc(256);
    fgets(inputcmd, 256, stdin);

    // Length of input line
    int length = strlen(inputcmd);

    // Removes the newline at the end of the input command
    if (length > 0 && inputcmd[length - 1] == '\n') {
        inputcmd[length - 1] = '\0';
    }

    return inputcmd;
}

void sighandler(int signum) {
    if (signum == SIGINT) {
        printf("\n>");
        bash_shell();
        fflush(stdout);
    } /*else if (signum == SIGTSTP) {
        kill(getpid(), SIGSTOP);
        fflush(stdout);
    }*/
}