#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	pid_t process = fork();
	if(process > 0){
		printf("Proces Rodzic - PID: %d\t PPID: %d\n",getpid(), getppid());
	} else if (process == 0){
		printf("Proces Dziecko - PID: %d\t PPID: %d\n", getpid(), getppid());
		wait(NULL);
	} else {
		printf("Blad");
	}
	return 0;
}

