#include "exec_commands.h"

int exec_commands(char *cmds) {
    *strrchr(cmds, '\n') = 0;
    char **parsedcmds = parseargs(cmds, ";");
    char *cmd = *parsedcmds;
    int n = 0;
    while (cmd) {
        if (token_checker(cmd)) {
            exec_special(cmd, token_checker(cmd));
        } else {
            char **parsedargs = parseargs(cmds, " ");
            exec_fork(parsedargs);
            free(parsedargs);
        }
        cmd = parsedcmds[++n];
    }
    free(cmd);
    free(cmds);
}

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

void exec_fork(char **parsedargs) {
    if (!strcmp(parsedargs[0], "")) {
        return;
    }
    if (!strcmp(parsedargs[0], "exit")) {
        exit(0);
    } else if (!strcmp(parsedargs[0], "cd")) {
        if (parsedargs[1]) {
            if (chdir(parsedargs[1])) {
                printf("Could not cd into %s becuase reasons\n", parsedargs[1]);
            }
        } else {
            chdir(parsedargs[1]);
        }
    } else {
        int pid;
        if (pid = fork()) {
            waitpid(pid, NULL, 0);
        } else {
            execvp(parsedargs[0], parsedargs);
            exit(0);
        }
    }
}

void exec_special(char *parsedargs, int token) {
    int n, c, b;
    char *exec;
    if (token == 2) {
        exec = strsep(&parsedargs, ">");
        if (token_checker(parsedargs)) {
            parsedargs = snipsnip(parsedargs);
            char backend[strlen(parsedargs)];
            strncpy(backend, parsedargs, strlen(parsedargs));
            char *this = strsep(&parsedargs, " ");
            n = open(this, O_CREAT | O_WRONLY, 0644);
            c = dup(STDOUT_FILENO);
            b = dup2(n, STDOUT_FILENO);
            exec_special(backend, token_checker(backend));
            dup2(c, b);
        } else {
            n = open(snipsnip(parsedargs), O_CREAT | O_WRONLY, 0644);
            c = dup(STDOUT_FILENO);
            b = dup2(n, STDOUT_FILENO);
            exec = snipsnip(exec);
            char **todo = parseargs(exec, " ");
            exec_fork(todo);
            free(todo);
            dup2(c, b);
            close(n);
        }
    } else if (token == 3) {
        exec = strsep(&parsedargs, "<");
        if (token_checker(parsedargs)) {
            parsedargs = snipsnip(parsedargs);
            char backend[strlen(parsedargs)];
            strncpy(backend, parsedargs, strlen(parsedargs));
            char *this = strsep(&parsedargs, " ");
            n = open(this, O_CREAT | O_WRONLY, 0644);
            c = dup(STDIN_FILENO);
            b = dup2(n, STDIN_FILENO);
            exec_special(backend, token_checker(backend));
            dup2(c, b);
        } else {
            n = open(snipsnip(parsedargs), O_CREAT | O_WRONLY, 0644);
            c = dup(STDIN_FILENO);
            b = dup2(n, STDIN_FILENO);
            exec = snipsnip(exec);
            char **todo = parseargs(exec, " ");
            exec_fork(todo);
            free(todo);
            dup2(c, b);
            close(n);
        }
    } else if (token == 4) {
        char **newargs = parseargs(parsedargs, "|");
        if (strcmp(newargs[1], "")) {
            FILE *fp;
            fp = popen(newargs[0], "r");
            if(!fp) {
                printf("Pipe went wrong\n");
                return;
            }
            c = dup(STDIN_FILENO);
            b = dup2(fileno(fp), STDIN_FILENO);
            char **nparsedargs = parseargs(snipsnip(newargs[1]), " ");
            exec_fork(nparsedargs);
            dup2(c, b);
            pclose(fp);
            free(nparsedargs);
            free(newargs);
        }
    }
}



// Checks if the token is a "special character"
int token_checker(char *token) {
    if (strchr(token, ';')) return 1;
    else if (strchr(token, '>')) return 2;
    else if (strchr(token, '<')) return 3;
    else if (strchr(token, '|')) return 4;
    else return 0;
}