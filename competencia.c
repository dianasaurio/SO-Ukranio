#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int arcg, char *argv[]){
	int shmid, *variable;
	key_t llave;

	llave = ftok(argv[1], 'K'); // 1

	if((shmid = shmget(llave, sizeof(int), IPC_CREAT | 0600)) == -1){// 2
		perror("Error en shmget");
		exit(-1);		
	}
	/*Nos vamos a la memoria compartida*/
	if((variable = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){// 3
		perror("Fallo de shmat");
		exit(-1);
	}

	*variable = 0;
	
	int n = atoi(argv[2]), i;

	pid_t pid;
	int estado;

	pid = fork();
	switch(pid){
		case -1: /* error en el fork */
			perror("Error en el fork");
			break;
		case 0: /* proceso hijo */
			//printf("Soy el hijo: PID %d; PPID = %d i = %d\n", getpid(), getppid(), ++i);
			for(i = 0; i < n; i++){
				//printf("%d\n", variable--);
				(*variable)--;
				//printf("%d, (hijo: %d, ppid(%d)) Variable = %d\n", i, getpid(), getppid(), *variable);
			}
			exit(0);
			break;
		default: /* proceso padre */
			//printf("Soy el padre: PID %d; PPID = %d i = %d\n", getpid(), getppid(), --i);
			for(i = 0; i < n; i++){
				//printf("%d\n", variable++);
				//*variable = *variable + 1;
				(*variable)++;
				//variable[0] = variable[0] + 1;
				//printf("%d, (padre: %d, ppid(%d)) Variable = %d\n", i, getpid(), getppid(), *variable);

			}
			wait(&estado);
			printf("(dos) Variable = %d\n", *variable);
			exit(0);
			
			
	}

	return 0;
}
