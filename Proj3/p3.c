/****************************************
*										*
* Proyecto 3 							*
* Sistemas Operativos					*
* Profesor: Ukranio Contreras			*
* Alumna: Sánchez Urbán Diana Pamela	*
* Grupo: 2CM4							*
*										*
*****************************************/

#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <poll.h>
#include <signal.h>

#define SEMAFORO_0 0
#define SEMAFORO_1 1
#define SEMAFORO_2 2
#define SEMAFORO_3 3

struct Empleado {
	char nombre[15];
	char inic[2];
	char apellido[15];
	char nss[13];
	char fecha_ncto[11];
	char direccion[30];
	char sexo[2];
	char salario[6];
	char nss_superv[13];
	char nd[2];
};

/***************************************************FUNCIONES****************************************************/

int leer_car(){
	char letra;
	char almacen[80];

	scanf("%s", &almacen);
	sscanf(almacen, "%c", &letra);
	return letra;
}

int min(a,b){
	if(a > b) return b;
	else return a;
}

int obtenCantidad(int salario1, int salario2){

	
	int aux1, aux2;

	srand(time(NULL));
	int cantidad = rand()%1000 + 1;
	

	if(salario2 == 0)
		cantidad = 0;

	else if ((salario2 < 1000) && (salario1 < 1000))
		cantidad = min(salario1, salario2);

	else if ((salario2 < 1000) || (salario1 < 1000))
		cantidad = min(salario1, salario2);

	else if(salario1 == 99999)
		cantidad = 0;

	aux1 = salario1 + cantidad;
	aux2 = salario2 - cantidad;

	while(1){
		if((aux1 >= 0 && aux1 <= 99999) && (aux2 >= 0 && aux2 <= 99999))
			break;
		else{
			cantidad = rand()%1000 + 1;
			aux1 = salario1 + cantidad;
			aux2 = salario2 - cantidad;

		}
	}

	return cantidad;
	
}

char *itoa(int n){

	static char retbuf[25];
	sprintf(retbuf, "%d", n);
	return retbuf;
}

void update(int op, int nss, int cantidad){

	FILE *archivo;
	struct Empleado registro;
	int salario;


	archivo=fopen("empleados.dat","r+b");
	if (!archivo){
		printf("No se pudo abrir el archivo! ):\n");
		return;
	}

	fseek(archivo,sizeof(struct Empleado)*(nss-1),SEEK_SET);
	fread(&registro,sizeof(struct Empleado),1,archivo);
	
	if(op >= 0){ //incremento
		salario = atoi(registro.salario);
		salario = salario + cantidad;
		strcpy(registro.salario, itoa(salario));
	}
	else{//decremento
		salario = atoi(registro.salario);
		salario = salario - cantidad;
		strcpy(registro.salario, itoa(salario));
	} 

	fseek(archivo,sizeof(struct Empleado)*(nss-1),SEEK_SET);
	fwrite(&registro, sizeof(struct Empleado), 1, archivo);
	
	fclose(archivo);

}

void Transaccion(){

	FILE *archivo;
	struct Empleado registroI, registroD;
	int offset1, cantidad, offset2;


	archivo=fopen("empleados.dat","rb+");
	if (!archivo){
		printf("No se pudo abrir el archivo! ):\n");
		return;
	}

	srand(getpid());
	offset1 = rand()%100000+1;
	offset2 = rand()%100000+1;

	fseek(archivo,sizeof(struct Empleado)*(offset1-1),SEEK_SET);
	fread(&registroI,sizeof(struct Empleado),1,archivo);
	fseek(archivo,sizeof(struct Empleado)*(offset2-1),SEEK_SET);
	fread(&registroD,sizeof(struct Empleado),1,archivo);
	cantidad = obtenCantidad(atoi(registroI.salario), atoi(registroD.salario));

	if(atoi(registroI.nss) > atoi(registroD.nss)){
		update(1, atoi(registroD.nss), cantidad);
		update(-1, atoi(registroI.nss), cantidad);
	}
	else {
		update(1, atoi(registroI.nss), cantidad);
		update(-1, atoi(registroD.nss), cantidad);
	}
	

	fclose(archivo);
	return;
}

void imprimeRegistros(){

	FILE *archivo;
	struct Empleado registro;


	archivo=fopen("empleados.dat","rb");
	if (!archivo){
		printf("No se pudo abrir el archivo! ):\n");
		return;
	}

	printf("NOMBRE | INIC | APELLIDO | NSS | FECHA_NAC | DIRECCION | SEXO | SALARIO | NSS_SUPERV | ND | \n\n");
	while(fread(&registro,sizeof(struct Empleado),1,archivo) == 1){
		printf("%s %s %s %s %s %s %s %s %s %s\n", registro.nombre, registro.inic, registro.apellido, registro.nss, registro.fecha_ncto, registro.direccion, registro.sexo, registro.salario, registro.nss_superv, registro.nd);
	}
	fclose(archivo);
	puts("");
	return;
}

int cuentaRegistros(char letra){

	int cta = 0;
	FILE *archivo;
	struct Empleado registro;

	archivo=fopen("empleados.dat","rb");
	if (!archivo){
		printf("No se pudo abrir el archivo! ):\n");
		return 1;
	}

	while(fread(&registro,sizeof(struct Empleado),1,archivo) == 1){
		if(registro.inic[0] == letra)
			cta ++;

	}
	fclose(archivo);
	return cta;
}

long long int obtenSuma(){

	long long int total = 0;
	FILE *archivo;
	struct Empleado registro;

	archivo=fopen("empleados.dat","rb");
	if (!archivo){
		printf("No se pudo abrir el archivo! ):\n");
		return 1;
	}

	while(fread(&registro,sizeof(struct Empleado),1,archivo) == 1){
		
		total = total + atoi(registro.salario);

	}
	fclose(archivo);
	return total;

}

/****************************************************************************************************************/

int main(int argc, char* argv[]){

	puts("Modo de uso: Este programa no recibe ningun argumento.\n");
	
	pid_t pid;
	int j = 0;
	int estado;
	struct Empleado registro;
	int shmid;
	key_t llave;
	int semid;
	struct sembuf operacion;
	int *variable;
	char letra;

/********************Creamos memoria compartida para el numero de transacciones********************/

	llave = ftok(argv[0], 'K'); 

	if((shmid = shmget(llave, sizeof((int)malloc(6)), IPC_CREAT | 0600)) == -1){
		perror("Error en shmget");
		exit(-1);		
	}
	if((variable = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
		perror("Fallo de shmat");
		exit(-1);
	}

/******************************************* SEMAFOROS *******************************************/

	if((semid = semget(llave, 4, IPC_CREAT | 0600)) == -1){
			perror("Error al ejecutar smget");
			exit(-1);
		}

		semctl(semid, SEMAFORO_0, SETVAL, 1);
		semctl(semid, SEMAFORO_1, SETVAL, 0);
		semctl(semid, SEMAFORO_2, SETVAL, 0);
		semctl(semid, SEMAFORO_3, SETVAL, 0);

/**************************************************************************************************/
	int x;
	variable[0]=0;
	for(j = 0; j < 4; j++){
		pid = fork();
		if(pid == 0)
			break;	
	}

	switch(j){
		case 0://Proceso hijo 0
			variable[j+1] = getpid();
			while(1){
				//DOWN EN SEMAFORO 0
				/*operacion.sem_flg = 0;
				operacion.sem_op = -1;
				operacion.sem_num = SEMAFORO_0;*/
				semop(semid, &operacion, 1);
				//TRANSACCION
				Transaccion();
				//incrementar contador transacciones
				(*variable)++;
				
				//UP EN 1
				/*operacion.sem_op = 1;
				operacion.sem_num = SEMAFORO_1;
				semop(semid, &operacion, 1);*/
			}
			break;
		case 1://Proceso hijo 1
			variable[j+1] = getpid();
			while(1){
				//DOWN EN SEMAFORO 1
				operacion.sem_flg = 0;
				operacion.sem_op = -1;
				operacion.sem_num = SEMAFORO_1;
				semop(semid, &operacion, 1);
				
				//TRANSACCION
				Transaccion();
				//incrementar contador transacciones
				(*variable)++;

				//UP EN 2
				operacion.sem_op = 1;
				operacion.sem_num = SEMAFORO_2;
				semop(semid, &operacion, 1);
			}
			break;
		case 2://Proceso hijo 2
			variable[j+1] = getpid();
			while(1){
				//DOWN EN SEMAFORO 2
				operacion.sem_flg = 0;
				operacion.sem_op = -1;
				operacion.sem_num = SEMAFORO_2;
				semop(semid, &operacion, 1);
				//TRANSACCION
				Transaccion();
				//incrementar contador transacciones
				(*variable)++;

				//UP EN 3
				operacion.sem_op = 1;
				operacion.sem_num = SEMAFORO_3;
				semop(semid, &operacion, 1);
			}
			break;
		case 3:
			variable[j+1] = getpid();
			while(1){//Proceso hijo 2
				//DOWN EN SEMAFORO 3
				operacion.sem_flg = 0;
				operacion.sem_op = -1;
				operacion.sem_num = SEMAFORO_3;
				semop(semid, &operacion, 1);
				//TRANSACCION
				Transaccion();
				//incrementar contador transacciones
				(*variable)++;

				//UP EN 0
				operacion.sem_op = 1;
				operacion.sem_num = SEMAFORO_0;
				semop(semid, &operacion, 1);
			}
			break;
		case 4:
			while(1){

				printf("Presione la tecla para ver la información correspondiente:\n\n");
				printf("Visualizar el numero de transacciones hasta el momento              1\n");
				printf("Visualizar el número de registros cuyo campo INIC es la letra...    2\n");
				printf("Obtener la suma del salario de todos los registros                  3\n");
				printf("Terminar                                                            4\n\n");

				scanf("%d", &x);


				switch(x){
					case 1: //Visualizar cantidad de transacciones

						//Accesamos a memoria compartida

						printf("\nTransacciones hasta el momento: %d\n\n\n", variable[0]);

						break;
					case 2: //Contar registros 


						//Contamos registros
						printf("\nIntroduzca INIC: \n");
						letra = leer_car();
						printf("\nRegistros con la letra %c en campo INIC: %d\n\n\n", letra,cuentaRegistros(letra));

						break;
					case 3: //Suma del salario
						semctl(semid, SEMAFORO_0, SETVAL, 0);
						semctl(semid, SEMAFORO_1, SETVAL, 0);
						semctl(semid, SEMAFORO_2, SETVAL, 0);
						semctl(semid, SEMAFORO_3, SETVAL, 0);

						printf("\nTOTAL SALARIOS: %lld\n\n\n", obtenSuma());

						semctl(semid, SEMAFORO_0, SETVAL, 1);

						break;
					case 4:
						//Matar prcesos hijos
						
						printf("Matando proceso... %d\n", variable[1]);
						kill(variable[1],SIGKILL);
						printf("Matando proceso... %d\n", variable[2]);
						kill(variable[2],SIGKILL);
						printf("Matando proceso... %d\n", variable[3]);
						kill(variable[3],SIGKILL);
						printf("Matando proceso... %d\n", variable[4]);
						kill(variable[4],SIGKILL);
						
						//Liberar memoria compartida
						shmctl(shmid, IPC_RMID, 0);
						//Terminar proceso padre
						exit(0);
						break;
					default:
						printf("Opcion no valida\n");
					
		
				}
			}
			break;

	}

	return 0;
}