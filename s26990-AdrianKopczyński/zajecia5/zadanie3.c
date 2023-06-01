#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Podaj dokladnie jeden argument jako wartosc.\n");
        return 1;
    }
    
    int value = atoi(argv[1]);
    pid_t pid = fork();
    
    if (pid < 0) {
        printf("Blad podczas tworzenia procesu potomnego.\n");
        return 1;
    } else if (pid == 0) {
    	/*Child*/
        printf("Proces potomny: Liczby nieparzyste od 1 do %d:\n", value);
        for (int i = 1; i <= value; i += 2) {
            printf("%d ", i);
        }
        printf("\n");
    } else {
        /*Parent*/
        int sum = 0;
        for (int i = 0; i <= value; i++) {
            sum += i;
        }
        wait(NULL);
        printf("Proces rodzica: Suma liczb od 0 do %d: %d\n", value, sum);
    }

    return 0;
}

