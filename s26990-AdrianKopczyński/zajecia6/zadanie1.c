#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>

void handler(int sig){
	printf("Otrzymano sygnal, program konczy dzialanie\n ");
	exit(0);

}

int main(){
	pid_t process;
	process = getpid();	
	printf("PID: %d\n", process);
	fflush(stdout);
	signal(SIGUSR1,handler);

	while(1){
		sleep(1);
	}



	return 0;
}

