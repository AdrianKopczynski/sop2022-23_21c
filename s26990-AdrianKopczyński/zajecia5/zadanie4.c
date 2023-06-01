#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main(){
	int i; int pCount = 100;
	for(i=1; i< pCount; i++){
		pid_t X=0;
		printf("PID: %d\t PPID: %d\n", getpid(), getppid());
		X = fork();		
		if(X > 0){
			wait(NULL);
			break;
		}
	}
	return 0;
}


