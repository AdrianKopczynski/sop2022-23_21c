#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main(){
	int i; int pCount = 100;
	pid_t masterPID = getpid();
	
	for(i=0; i< pCount; i++){
		pid_t x=0;
		x = fork();		
		if(x == 0){
			printf("PID: %d\t PPID: %d\n", getpid(), getppid());
			sleep(5);
			break;
		}
	}
	
	if(masterPID == getpid()){
		waitpid(-1,NULL,0);
		printf("Rodzic %d przestal czekac\n", getpid());
	}
	return 0;
}

