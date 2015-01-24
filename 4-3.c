#include <stdio.h>
#include <sys/types.h>

main(){
	pid_t pid;
	int j;

	for(j=0;j<10;j++){
		pid = fork();
		if(pid==0)
			break;
	}


	printf("EL padre del proceso %d es %d, j = %d\n", getpid(), getppid(), j);
	sleep(3);
}