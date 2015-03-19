#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SEMAFORO_PADRE 0
#define SEMAFORO_HIJO 1

int main(int arcg, char *argv[]){

	int shmid, *variable, semid;
	key_t llave;
	struct sembuf operacion;

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

	if((semid = semget(llave, 2, IPC_CREAT | 0600)) == -1){
		perror("Error al ejecutar smget");
		exit(-1);
	}

	//inicializando semaforos
	semctl(semid, SEMAFORO_PADRE, SETVAL, 0);
	semctl(semid, SEMAFORO_HIJO, SETVAL, 1);
	
	int n = atoi(argv[2]), i;

	pid_t pid;
	int estado;

	pid = fork();
	switch(pid){
		case -1: /* error en el fork */
			perror("Error en el fork");
			break;
		case 0: /* proceso hijo */

			for(i = 0; i < n; i++){
				//hacemos down en el semaforo del hijo
				operacion.sem_flg = 0;
				operacion.sem_op = -1;
				operacion.sem_num = SEMAFORO_HIJO;

				semop(semid, &operacion, 1);
				(*variable)++;
				printf("\tSoy el hijo\n");
				//hacemos up en el padre
				operacion.sem_op = 1;
				operacion.sem_num = SEMAFORO_HIJO;
				semop(semid, &operacion, 1);
			}
			exit(0);
			break;
		default: /* proceso padre */

			for(i = 0; i < n; i++){
				//hacemos down en el padre
				operacion.sem_flg = 0;
				operacion.sem_op = -1;
				operacion.sem_num = SEMAFORO_HIJO;
				semop(semid, &operacion, 1);
				(*variable)--;
				printf("Soy el padre\n");
				//hacemos up en el hijo
				operacion.sem_op = 1;
				operacion.sem_num = SEMAFORO_HIJO;
				semop(semid, &operacion, 1);
			}
			wait(&estado);
			printf("(dos) Variable = %d\n", *variable);
			exit(0);
			
			
	}

	return 0;
}
