#include "exec_commands.h"

/*======== void exec_commands() ==========
    Inputs: char *cmds
    Returns: 

    Takes an input string from rd_line and determines
    whether to pass it to the exec_form() function or
    the exec_special() function.
    ====================*/

void exec_commands(char *cmds) {
    *strrchr(cmds, '\n') = 0; // Sets the last occurance of "\n" in cmds to 0.
    char **parsedcmds = parseargs(cmds, ";");
    char *cmd = *parsedcmds;
    int n = 0;
    while (cmd) {
        cmd = snipsnip(cmd); // Erases whitespace at the beginning and end
        if (token_checker(cmd) > 1) { // If a token is detected
            exec_special(cmd, token_checker(cmd));
        } else {
            char **parsedargs = parseargs(cmds, " ");
            exec_fork(parsedargs);
            free(parsedargs);
        }
        cmd = parsedcmds[++n];
    }
    free(cmds);
}

/*======== char *snipsnip() ==========
    Inputs: char *car
    Returns: char *

    Removes whitespace from the beginning or end of a string.
    ====================*/

char *snipsnip(char *car) {
    char *end = car + strlen(car) - 1;
    while (*car && isspace(*car)) {
        car++;
    }
    while (end > car && isspace(*end)) {
        *end-- = '\0';
    }
    return car;
}

/*======== void exec_fork() ==========
    Inputs: char **parsedargs
    Returns: void

    Executes hardcoded exceptions for exit and cd if they are detected.
    Otherwise forks and allows the child to execute the command.
    ====================*/

void exec_fork(char **parsedargs) {
    if (!strcmp(parsedargs[0], "exit")) { // exit
        exit(0);
    } else if (!strcmp(parsedargs[0], "cd")) { // cd
        if (parsedargs[1]) {
            if (chdir(parsedargs[1])) {
                printf("Could not cd into %s becuase reasons\n", parsedargs[1]);
            }
        } else {
            chdir(parsedargs[1]);
        }
    } else {
        int pid;
        if (pid = fork()) { // Forks
            waitpid(pid, NULL, 0);
        } else {
            execvp(parsedargs[0], parsedargs);
            exit(0);
        }
    }
}

/*======== void exec_special() ==========
    Inputs: char *parsedargs, int token
    Returns: void

    Takes a single command + its arguments and a token.
    The token tells the function whether to execute the
    ">", "<", or "|" path.
    ====================*/

void exec_special(char *parsedargs, int token) {
    int n, c, b;
    char *exec;
    if (token == 2) { // If ">"
        exec = strsep(&parsedargs, ">");
        if (token_checker(parsedargs)) {
            parsedargs = snipsnip(parsedargs);
            char backend[strlen(parsedargs)];
            strncpy(backend, parsedargs, strlen(parsedargs));
            char *this = strsep(&parsedargs, " ");
            n = open(this, O_CREAT | O_WRONLY, 0644);
            c = dup(STDOUT_FILENO);
            b = dup2(n, STDOUT_FILENO); // Swaps STDOUT with the right side of >
            exec_special(backend, token_checker(backend));
            dup2(c, b); // Resets file table
            close(n);
        } else {
            n = open(snipsnip(parsedargs), O_CREAT | O_WRONLY, 0644);
            c = dup(STDOUT_FILENO);
            b = dup2(n, STDOUT_FILENO); // Swaps STDOUT with the right side of >
            exec = snipsnip(exec);
            char **todo = parseargs(exec, " "); // todo = commands to run
            exec_fork(todo);
            free(todo);
            dup2(c, b); // Resets file table
            close(n);
        }
    } else if (token == 3) { // If "<"
        exec = strsep(&parsedargs, "<");
        if (token_checker(parsedargs)) {
            parsedargs = snipsnip(parsedargs);
            char backend[strlen(parsedargs)];
            strncpy(backend, parsedargs, strlen(parsedargs));
            char *this = strsep(&parsedargs, " ");
            n = open(this, O_CREAT | O_WRONLY, 0644);
            c = dup(STDIN_FILENO);
            b = dup2(n, STDIN_FILENO); // Swaps STDIN with the right side of <
            exec_special(backend, token_checker(backend));
            dup2(c, b); // Resets file table
            close(n);
        } else {
            n = open(snipsnip(parsedargs), O_CREAT | O_WRONLY, 0644);
            c = dup(STDIN_FILENO);
            b = dup2(n, STDIN_FILENO); // Swwaps STDIN with the right side of <
            exec = snipsnip(exec);
            char **todo = parseargs(exec, " ");
            exec_fork(todo);
            free(todo);
            dup2(c, b); // Resets file table
            close(n);
        }
    } else if (token == 4) { // If "|"
        char **newargs = parseargs(parsedargs, "|");
        if (strcmp(newargs[1], "")) {
            FILE *fp;
            fp = popen(newargs[0], "r");
            if(!fp) {
                printf("Pipe went wrong\n");
                return;
            }
            c = dup(STDIN_FILENO);
            b = dup2(fileno(fp), STDIN_FILENO); // Swaps STDIN with the descriptor of the file
            char **nparsedargs = parseargs(snipsnip(newargs[1]), " ");
            exec_fork(nparsedargs);
            dup2(c, b); // Resets the file table
            pclose(fp);
            free(nparsedargs);
            free(newargs);
        }
    }
}

/*======== int token_checker() ==========
    Inputs: char *token
    Returns: int

    Checks if the input character is ";", ">", "<", or "|"
    and returns 1, 2, 3, 4 respectively.
    ====================*/

int token_checker(char *token) {
    if (strchr(token, ';')) return 1;
    else if (strchr(token, '>')) return 2;
    else if (strchr(token, '<')) return 3;
    else if (strchr(token, '|')) return 4;
}