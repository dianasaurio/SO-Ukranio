#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEMAFORO_1 0
#define SEMAFORO_2 1
#define SEMAFORO_3 2

int main(int argc, char* argv[]){
	
	int semid, pid, j = 10, i;
	struct sembuf operacion;
	key_t llave;

	printf("sem_num: %d, sem_op: %d, sem_flg: %d\n", operacion.sem_num, operacion.sem_op, operacion.sem_flg);

	llave = ftok(argv[0], 'U');

	if((semid = semget(llave, 5, IPC_CREAT | 0600)) == -1){
		perror("Error al ejecutar smget");
		exit(-1);
	}

	semctl(semid, SEMAFORO_1, SETVAL, 1);
	semctl(semid, SEMAFORO_2, SETVAL, 0);
	semctl(semid, SEMAFORO_3, SETVAL, 0);

	/*Creamos tres procesos*/

	for(i=0;i<=3;i++){
		pid = fork();
		if(pid==0)
			break;
	}

	/*if(pid > 0)
		wait(&j);*/

	int x;
	switch(i){

		case 0:
			while(j){
				//Hacemos down en semaforo 1	
				scanf("%d", &x);
				operacion.sem_flg = 0;
				operacion.sem_op = -1;
				operacion.sem_num = SEMAFORO_1;
				semop(semid, &operacion, 1);
				//Imprimimos
				printf("SOY EL PROCESO %d. IMPRESION: %d\n", i,j--);
				//Hacemos up en los semaforos 2 y 3
				operacion.sem_op = 1;
				operacion.sem_num = SEMAFORO_2;
				semop(semid, &operacion, 1);
				//operacion.sem_num = SEMAFORO_3;
				//semop(semid, &operacion, 1);
			}
			semctl(semid, 0, IPC_RMID, 0);
			break;
		case 1:
			while(j){
				//Hacemos down en semaforo 2	
				operacion.sem_flg = 0;
				operacion.sem_op = -1;
				operacion.sem_num = SEMAFORO_2;
				semop(semid, &operacion, 1);
				//Imprimimos
				printf("SOY EL PROCESO %d. IMPRESION: %d\n", i,j--);
				//Hacemos up en los semaforos 1 y 3
				operacion.sem_op = 1;
				operacion.sem_num = SEMAFORO_3;
				semop(semid, &operacion, 1);
				//operacion.sem_num = SEMAFORO_3;
				//semop(semid, &operacion, 1);
			}
			semctl(semid, 0, IPC_RMID, 0);
			break;
		case 2:
			while(j){
				//Hacemos down en semaforo 3	
				operacion.sem_flg = 0;
				operacion.sem_op = -1;
				operacion.sem_num = SEMAFORO_3;
				semop(semid, &operacion, 1);
				//Imprimimos
				printf("SOY EL PROCESO %d. IMPRESION: %d\n", i,j--);
				//Hacemos up en los semaforos 1 y 2
				operacion.sem_op = 1;
				operacion.sem_num = SEMAFORO_1;
				semop(semid, &operacion, 1);
				//operacion.sem_num = SEMAFORO_2;
				//semop(semid, &operacion, 1);
			}
			semctl(semid, 0, IPC_RMID, 0);
			break;
		case 3:

			while(j){
				printf("Soy el proceso padre!!\n");
				j--;
			}
			break;
	}
	
}