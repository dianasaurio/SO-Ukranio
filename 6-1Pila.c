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

	char caracter;
	int i, j;





	while(1){
		printf("\nIntroduzca m para meter un caracter a la pila, s para sacar un valor, v para visualizarla y t para terminar:\n");

		switch(leer_car()){
			case 't':
				/* Libera la memoria compartida */
				shmctl(shmid, IPC_RMID, 0);
				exit(0);
			case 'v':
				/* Visualiza la variable */
				j = 0;
				while(*(variable+j)!='\0'){
					printf("%c ", *(variable+j));
					j++;
				}
				puts("");
				break;
			case 'm':
				printf("Nuevo valor de la variable en memoria compartida: \n");
				caracter = leer_car();
				i = 0;
				while(variable[i] != '\0')
					i++;

				if(i>9)
					printf("Pila llena! ):\n");
				else
					*(variable + i) = caracter;
				break;
			case 's':
				printf("Sacando caracter de la pila\n");

				i = 0;
				while(variable[i] != '\0')
					i++;
				if(i==0)
					printf("Pila vacia! ):\n");
				else
					variable[i-1] = '\0';

				break;
			default:
				printf("Se introdujo una letra incorrecta\n");
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