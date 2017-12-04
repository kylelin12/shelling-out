#include "shell.h"

int main() {

    signal(SIGINT, sighandler);

    while (1) {
        printf(">");
        bash_shell();
    }

    return 0;
}