#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void receive(const char *user) {
	char filename[20];
    	sprintf(filename, "/tmp/chat_%s.txt", user);

    	FILE *file = fopen(filename, "r");
    	if (file == NULL) {
        	printf("Nie mozna otworzyc pliku.\n");
        	exit(1);
    	}

    	char message[100];

    	while (fgets(message, sizeof(message), file) != NULL) {
        	printf("Wiadomosc od %s: %s", user, message);
    	}

    	fclose(file);
}

void send(const char *user, const char *message) {
    	char filename[20];
    	sprintf(filename, "/tmp/chat_%s.txt", user);

    	FILE *file = fopen(filename, "w");
    	if (file == NULL) {
        	printf("Nie mozna otworzyc pliku.\n");
        	exit(1);
    	}

    	fputs(message, file);
    	fclose(file);
}

int main() {

	char message[100];
	
	while(1){
    	
		pid_t pid = fork();

		if(pid < 0){
			printf("Blad");
			exit(1);
		}else if(pid == 0){
			const char *user = "A";
			receive("B");
			printf("Wpisz wiadomosc: ");
			fgets(message, sizeof(message), stdin);

			send(user, message);
			break;
		}else{
			wait(NULL);
			const char *user = "B";
			receive("A");
			fgets(message, sizeof(message), stdin);

			send(user, message);
		}
		
	}
	return 0;
}

