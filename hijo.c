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

	//printf("sem_num: %d, sem_op: %d, sem_flg: %d\n", operacion.sem_num, operacion.sem_op, operacion.sem_flg);

	llave = ftok(argv[1], 'U');

	if((semid = semget(llave, 5, IPC_CREAT | 0600)) == -1){
		perror("Error al ejecutar smget");
		exit(-1);
	}

	semctl(semid, SEMAFORO_HIJO, SETVAL, 0);
	//semctl(semid, SEMAFORO_PADRE, SETVAL, 0);

	while(j){
		/*Se realiza la operación DOWN en el semaforo del proceso hijo*/

		operacion.sem_flg = 0;
		operacion.sem_op = -1;
		operacion.sem_num = SEMAFORO_HIJO;
		//printf("Down en sem hijo: sem_num: %d, sem_op: %d, sem_flg: %d\n", operacion.sem_num, operacion.sem_op, operacion.sem_flg);
		semop(semid, &operacion, 1);

		printf("SOY EL PROCESO HIJO. IMPRESION: %d\n", j--);
		sleep(3);
		//j--;
		//printf("HIJO DOWN: sem_num: %d, sem_op: %d, sem_flg: %d\n", operacion.sem_num, operacion.sem_op, operacion.sem_flg);
		//printf("SEM ID EN HIJO: %d\n", semid);

		/*Se realiza la operación UP en el semaforo del proceso padre*/

		operacion.sem_op = 1;
		operacion.sem_num = SEMAFORO_PADRE;
		//printf("Up en sem padre: sem_num: %d, sem_op: %d, sem_flg: %d\n", operacion.sem_num, operacion.sem_op, operacion.sem_flg);
		semop(semid, &operacion, 1);

		//printf("HIJO UP: sem_num: %d, sem_op: %d, sem_flg: %d\n", operacion.sem_num, operacion.sem_op, operacion.sem_flg);
		//printf("SEM ID EN HIJO: %d\n", semid);
	}
	
	/*Borramos el semaforo*/
	semctl(semid, 0, IPC_RMID, 0);
	
}