#include "bash_shell.h"

int bash_shell() {
    
    // Runs the rd_line() function to return a string containing the input from stdin
    char *inputcmd = rd_line();

    // Execute the commands from a forked process
    exec_commands(inputcmd);

    return 0;
}

// Returns a string containing the input from stdin
char *rd_line() {
    // Stores the input taken from stdin to a character pointer
    char *inputcmd = malloc(256);
    fgets(inputcmd, 256, stdin);

    // Length of input line
    int length = strlen(inputcmd);

    return inputcmd;
}

void sighandler(int signum) {
    if (signum == SIGINT) {
        printf("\n>");
        bash_shell();
        fflush(stdout);
    }
}