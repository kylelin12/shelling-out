#include "bash_shell.h"

/*======== int bash_shell() ==========
    Inputs: 
    Returns: 0 

    Runs rd_line() to read a line from stdin.
    Passes the char* from rd_line() into exec_commands().
    Returns 0 if nothing goes wrong.
    ====================*/

int bash_shell() {
    
    // Runs the rd_line() function to return a string containing the input from stdin
    char *inputcmd = rd_line();

    // Execute the commands from a forked process
    exec_commands(inputcmd);

    return 0;
}

 /*======== char *rd_line() ==========
    Inputs: 
    Returns: Char pointer containing the input string 

    Allocates memory to a char pointer.
    Uses fgets() to read from stdin to the char pointer.
    Returns the pointer.
    ====================*/

char *rd_line() {
    // Stores the input taken from stdin to a character pointer
    char *inputcmd = malloc(256);
    fgets(inputcmd, 256, stdin);

    // Length of input line
    int length = strlen(inputcmd);

    return inputcmd;
}

/*======== void sighandler() ==========
    Inputs: int
    Returns: void 

    Takes an input int which is received from signal() in main().
    If SIGINT is the input, re-runs bash_shell() and clears the buffer.
    If SIGSTSP is the input, sends a SIGSTOP signal to the process. **Broken and removed**
    ====================*/

void sighandler(int signum) {
    if (signum == SIGINT) {
        printf("\n>");
        bash_shell();
        fflush(stdout);
    }
}