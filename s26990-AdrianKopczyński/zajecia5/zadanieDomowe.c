#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	pid_t procesB; pid_t procesC; pid_t procesD; pid_t procesE; pid_t procesF; pid_t procesG;

	printf("A PID:%d\t PPID:%d\n", getpid(), getppid());
	procesB = fork();
	if(procesB == 0){
		printf("B PID: %d\t PPID: %d\n", getpid(), getppid());
		procesD = fork();
		if(procesD == 0){
			printf("D PID: %d\t PPID: %d\n", getpid(), getppid());
			exit(0);
		} else if (procesD > 0){
			wait(NULL);
		} else {
			printf("Blad");
		}
		procesE = fork();
		if(procesE == 0){
			printf("E PID: %d\t PPID: %d\n", getpid(), getppid());
			exit(0);
		} else if (procesE > 0){
			wait(NULL);
		} else {
			printf("Blad");
		}
	} else if (procesB > 0){
		procesC = fork();
		if(procesC == 0){
			printf("C PID: %d\t PPID:%d\n", getpid(), getppid());
			procesF = fork();
			if(procesF == 0){
				printf("F PID: %d\t PPID:%d\n", getpid(), getppid());
				exit(0);
			} else if (procesF > 0){
				wait(NULL);
			} else {
				printf("Blad");
			}
			procesG = fork();
			if(procesG == 0){
				printf("G PID: %d\t PPID: %d\n", getpid(), getppid());
				exit(0);			
			} else if (procesG > 0){
				wait(NULL);
			} else {
				printf("Blad");
			}
		}else if (procesC > 0){
			waitpid(procesC, NULL, 0);
		} else {
			printf("Blad");
		}
	}
	return 0;
}

