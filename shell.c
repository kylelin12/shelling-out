#include "shell.h"

int main() {

    signal(SIGINT, &sighandler);
    signal(SIGTSTP, &sighandler);

    while (1) {
        printf(">");
        bash_shell();
    }

    return 0;
}