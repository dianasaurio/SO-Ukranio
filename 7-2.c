#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEMAFORO_PADRE 0
#define SEMAFORO_HIJO 1

int main(int argc, char* argv[]){
	
	int semid, pid, j = 10;
	struct sembuf operacion;
	key_t llave;

	printf("sem_num: %d, sem_op: %d, sem_flg: %d\n", operacion.sem_num, operacion.sem_op, operacion.sem_flg);

	llave = ftok(argv[0], 'U');

	if((semid = semget(llave, 2, IPC_CREAT | 0600)) == -1){
		perror("Error al ejecutar smget");
		exit(-1);
	}

	semctl(semid, SEMAFORO_HIJO, SETVAL, 0);
	semctl(semid, SEMAFORO_PADRE, SETVAL, 1);

	/*se crea el proceso hijo*/
	if((pid = fork()) == -1){
		perror("Error al ejecutar fork");
		exit(-1);
	}else if(pid == 0){
		/*Código correspondiente al proceso hijo*/
		while(j){
			/*Se realiza la operación DOWN en el semaforo del proceso hijo*/

			operacion.sem_flg = 0;
			operacion.sem_op = -1;
			operacion.sem_num = SEMAFORO_HIJO;
			semop(semid, &operacion, 1);

			printf("SOY EL PROCESO HIJO. IMPRESION: %d\n", j--);
			//j--;
			//printf("HIJO DOWN: sem_num: %d, sem_op: %d, sem_flg: %d\n", operacion.sem_num, operacion.sem_op, operacion.sem_flg);
			//printf("SEM ID EN HIJO: %d\n", semid);

			/*Se realiza la operación UP en el semaforo del proceso padre*/

			operacion.sem_op = 1;
			operacion.sem_num = SEMAFORO_PADRE;
			semop(semid, &operacion, 1);

			//printf("HIJO UP: sem_num: %d, sem_op: %d, sem_flg: %d\n", operacion.sem_num, operacion.sem_op, operacion.sem_flg);
			//printf("SEM ID EN HIJO: %d\n", semid);
		}
		/*Borramos el semaforo*/
		semctl(semid, 0, IPC_RMID, 0);
	}else{
		/*Codigo correspondiente al proceso padre*/
		while(j){
			/*Se realiza la operación DOWN en el semaforo del proceso padre*/
			operacion.sem_flg = 0;
			operacion.sem_op = -1;
			operacion.sem_num = SEMAFORO_PADRE;

			semop(semid, &operacion, 1);

			printf("SOY EL PROCESO PADRE. IMPRESION: %d\n", j--);
			//j--;
			//printf("PADRE DOWN: sem_num: %d, sem_op: %d, sem_flg: %d\n", operacion.sem_num, operacion.sem_op, operacion.sem_flg);
			//printf("SEM ID EN PADRE: %d\n", semid);

			/*Se realiza la operación UP en el semaforo del proceso hijo*/
			operacion.sem_op = 1;
			operacion. sem_num = SEMAFORO_HIJO;
			semop(semid, &operacion, 1);
			//printf("PADRE UP: sem_num: %d, sem_op: %d, sem_flg: %d\n", operacion.sem_num, operacion.sem_op, operacion.sem_flg);
			//printf("SEM ID EN PADRE: %d\n", semid);

		}
		/*Borramos el semaforo*/
		semctl(semid, 0, IPC_RMID, 0);
	}
}