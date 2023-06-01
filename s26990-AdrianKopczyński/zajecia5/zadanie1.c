#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
	int data;
	printf("PID: %d\t", getpid());
	printf("PPID: %d\t", getppid());
	printf("\n");
	scanf("%d", &data);
	return 0;
}

