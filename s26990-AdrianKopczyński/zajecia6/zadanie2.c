#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void handler() {
    printf("Wykryto probe uruchomienia drugiej instancji programu\n");
}

void handler2(int sig) {
    remove("/tmp/lock");
    exit(0);
}

int main() {
    struct sigaction new_action;
    new_action.sa_handler = handler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;
    pid_t process;
    FILE* file;
    file = fopen("/tmp/lock", "r");
    if (file == NULL) {
        file = fopen("/tmp/lock", "a+");
        if (file == NULL) {
            printf("Nie mozna utworzyc pliku lock\n");
            return 1;
        }
        process = getpid();
        fprintf(file, "PID:%d\n", process);
        fflush(file);
        signal(SIGINT, handler2);
        sigaction(SIGUSR1, &new_action, NULL);
        while (1) {
            sleep(1);
        }
    } else {
        char line[100];
        pid_t process2;
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
            process2 = atoi(line + 4);
        }
        sigaction(SIGUSR1, &new_action, NULL);
        kill(process2, SIGUSR1);
        fclose(file);
        exit(0);
    }
    return 0;
}

