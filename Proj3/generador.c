#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

struct registro_EMPLEADO {
	char nombre[15];
	char inic[2];
	char apellido[15];
	char nss[13];
	char fecha_ncto[11];
	char direccion[30];
	char sexo[2];
	char salario[6];
	char nss_superv[13];//2013630391
	char nd[2];
};

int main(int argc, char *argv[]){
	long i, trabajadores;
	int	j, fd_destino, new_year;
	char *tiempo, year[5];
	struct registro_EMPLEADO registro;
	struct tm *fecha;
	time_t t;

	if(argc !=	5){
		fprintf(stderr,	"Forma de uso: %s su_nombre su_matricula No.registros archivo_EMPLEADO\n", argv[0]);
		exit(-1);
	}

	time(&t);
	fecha = localtime(&t);
	
	if((fd_destino = open(argv[4], O_WRONLY|O_TRUNC|O_CREAT,0666)) == -1){
		perror(argv[2]);
		exit(-1);
	}

	trabajadores = atol(argv[3]);
	bzero((char*)(&registro),sizeof(registro));
	for(i =	1; i <= trabajadores; i++){

		sprintf(registro.nombre,"%s", argv[1]);
		sprintf(registro.nss,"%12d", i);

		for(j=0; j<	14; j++)
			sprintf(&registro.apellido[j],"%c",65+ rand()%10);

		sprintf(registro.inic,"%c", registro.apellido[13]);
		fecha->tm_mon = i%12;
		fecha->tm_mday =1+ i%28;
		tiempo = asctime(fecha);
		strncpy(year, &tiempo[20],4);
		new_year = atoi(year)-fecha->tm_mday;
		sprintf(registro.fecha_ncto,"%c%c%c%c%c%4d",tiempo[8],tiempo[9],tiempo[4],tiempo[5],tiempo[6],new_year);
		sprintf(registro.nd,"%d", i%9+1);
		sprintf(registro.direccion,"123456789012345678901234567890");

		if((i%2) ==	0)
			sprintf(registro.sexo,"%s","M");
		else
			sprintf(registro.sexo,"%s","F");

		sprintf(registro.salario,"%d", (rand()%75000));
		sprintf(registro.nss_superv,"%s", argv[2]);
		write(fd_destino, &registro,sizeof(struct registro_EMPLEADO));

	}
	close(fd_destino);
}
