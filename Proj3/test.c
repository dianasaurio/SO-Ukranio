#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>

struct Empleado{
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

char *itoa(int n){
	static char retbuf[25];
	sprintf(retbuf, "%d", n);
	return retbuf;
}

void imprimeRegistros(){

	FILE *archivo;
	struct Empleado registro;


	archivo=fopen("empleados.dat","rb");//registros.txt
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
		printf("Viejo salario: %d\n", salario);
		salario = salario + cantidad;
		printf("Nuevo salario: %d\n", salario);
		strcpy(registro.salario, itoa(salario));
		printf("INC salario del registro: %s\n", registro.salario);	
	}
	else{//decremento
		salario = atoi(registro.salario);
		printf("Viejo salario: %d\n", salario);
		salario = salario - cantidad;
		printf("Nuevo salario: %d\n", salario);
		strcpy(registro.salario, itoa(salario));
		printf("DEC salario del registro: %s\n", registro.salario);	
	} 

	fseek(archivo,sizeof(struct Empleado)*(nss-1),SEEK_SET);
	//write(archivo, &registro,sizeof(struct Empleado));
	fwrite(&registro, sizeof(struct Empleado), 1,archivo);
	
	fclose(archivo);

}

int main(){
	struct Empleado r1;

	imprimeRegistros();


	//update(1, 1, 500);
	//update(-1, 2, 500);

	//imprimeRegistros();
	printf("TOTAL SALARIOS: %lld \n", obtenSuma());


	//****************Transacción******************

	//elegir registro aleatorio


	//************Fin de transacción**************

	return 0;
}

int menu(){

	struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI };
	int opcion;

	printf("Presione la tecla para ver la información correspondiente:\n\n");
	printf("Visualizar el numero de transacciones hasta el momento              1\n");
	printf("Visualizar el número de registros cuyo campo INIC es la letra...    2\n");
	printf("Obtener la suma del salario de todos los registros                  3\n");
	printf("Terminar                                                            4\n\n");

	while(1){
		if(poll(&mypoll, 1, 100)){
			//printf("Listo para recibir datos: \n");
			scanf("%d", &opcion);
			break;//return opcion;
		}else{
			//printf("Menu dormido!\n");
			usleep(100000);
			//printf("Listo para recibir datos: \n");
		}
	}
	return opcion;

}

