#include <stdio.h>
#include <sys/types.h>

int main(){
	
	pid_t pid;
	int j = 0;

	for(j = 0; j < 10; j++){
		pid = fork();
		if(pid == 0)
			break;	
	}
	//pid = fork();
	printf("El padre del proceso %d es %d, j = %d\n", getpid(), getppid(), j);
	sleep(3);

	return 0;
}