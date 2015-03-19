#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int arcg, char *argv[]){
	int shmid, *variable;
	key_t llave;

	llave = ftok(argv[0], 'K'); // 1

	if((shmid = shmget(llave, sizeof(int), IPC_CREAT | 0600)) == -1){// 2
		perror("Error en shmget");
		exit(-1);		
	}
	/*Nos vamos a la memoria compartida*/
	if((variable = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){// 3
		perror("Fallo de shmat");
		exit(-1);
	}

	while(1){
		printf("\nIntroduzca m para modificar el valor de la variable, v para visualizarla y t para terminar:\n");

		switch(leer_car()){
			case 't':
				/* Libera la memoria compartida */
				shmctl(shmid, IPC_RMID, 0);
				exit(0);
			case 'v':
				/* Visualiza la variable */
				printf("Variable = %d\n", *variable);
				break;
			case 'm':
				printf("NUuevlo valor de la variable en memoria compartida: \n");
				scanf("%d", variable);
				break;
			default:
				printf("Se introdujo una letra incorrecta = \n");
				break;
		}
	}



	return 0;
}

int leer_car(){
	char letra;
	char almacen[80];

	scanf("%s", &almacen);
	sscanf(almacen, "%c", &letra);
	return letra;
}