#include "exec_commands.h"

int exec_commands(char** parsedargs) {
    char **cmds;
    char **backcmds;

    int cmdslength, restofcmdslength;
    for (cmdslength = 0; parsedargs[cmdslength]; cmdslength+=1){}

    int i;
    for (i = 0; parsedargs[i]; i++) {
        int token_type = token_checker(parsedargs[i]);
        // If the token is a ';'
        if (token_type == 1) {
            restofcmdslength = cmdslength - i - 1;
            cmds = malloc(i * 8);
            backcmds = malloc(restofcmdslength * 8);
            memcpy(cmds, parsedargs, i * 8);
            memcpy(backcmds, parsedargs + i + 1, restofcmdslength * 8);
            if (fork() == 0) {
                execvp(cmds[0], cmds);
                exit(0);
            } else {
                wait(0);
                printf("\n");
                free(cmds);
                exec_commands(backcmds);
            }
            return 0;
        } else if (token_type == 2) { // If the token is a '>'
            restofcmdslength = cmdslength - i - 2;

            int pipefd[2];
            int pid;

            cmds = malloc(i * 8);
            memcpy(cmds, parsedargs, i);
            memcpy(backcmds, parsedargs + i + 1, restofcmdslength * 8);

            char **cmdsright;

            i++;
            restofcmdslength = cmdslength - i - 1;

            cmdsright = malloc(i * 8);
            memcpy(cmdsright, parsedargs, (i - 1) * 8);

            pipe(pipefd);
            pid = fork();
            if (fork() == 0) {
                dup2(pipefd[0], 0);
                close(pipefd[1]);
                execvp(cmdsright[0], cmdsright);
            } else {
                dup2(pipefd[1], 1);
                close(pipefd[0]);
                execvp(cmds[0], cmds);
            }

            free(cmds);
            free(cmdsright);
            return 0;
        } else if (token_type == 3) { // If the token is a '<'
            restofcmdslength = cmdslength - i - 1;
            return 0;
        } else if (token_type == 4) { // If the token is a  '|'
            restofcmdslength = cmdslength - i - 1;
            return 0;
        }
    }

    if (fork() == 0) {
        execvp(parsedargs[0], parsedargs);
        exit(0);
    } else {
        wait(0);
    }

    return 0;
}

// Checks if the token is a "special character"
int token_checker(char *token) {
    if (strchr(token, ';')) return 1;
    else if (strpbrk(token, ">>")) return 22;
    else if (strchr(token, '>')) return 2;
    else if (strpbrk(token, "<<")) return 33;
    else if (strchr(token, '<')) return 3;
    else if (strchr(token, '|')) return 4;
    else return 0;
}