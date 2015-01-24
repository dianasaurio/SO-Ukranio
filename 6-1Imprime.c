#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int arcg, char *argv[]){
	int shmid, *variable;
	key_t llave;

	llave = ftok(argv[1], 'K'); // 1
	printf("llave: %d\n", llave);

	if((shmid = shmget(llave, sizeof((int)malloc(10)), IPC_CREAT | 0600)) == -1){// 2
		perror("Error en shmget");
		exit(-1);		
	}
	/*Nos vamos a la memoria compartida*/
	if((variable = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){// 3
		perror("Fallo de shmat");
		exit(-1);
	}

	int j = 0;

	while(1){
		j = 0;
		while(*(variable+j)!='\0'){
			printf("%c ", *(variable+j));
			j++;
		}
		puts("");
		sleep(1);
		system("clear");
	}


	return 0;
}

