#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int i = 10, pid;

	/*Creación del proceso hijo*/
	if((pid = fork()) == -1){
		perror("fork");
		exit(-1);
	}else if(pid == 0){
		while(i){
			printf("Proceso hijo: %d\n", i--);
		}
	}else {
		while(i){
			printf("Proceso padre: %d \n", i--);
		}
	}
}