#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char buffer [4097];

int main(int argc, char const *argv[])
{
	int nbytes, origen, destino;
	if (argc != 3){

		printf("Forma de uso: %s archivo_origen archivo_destino\n",argv[0]);
		exit (-1);
	}
/*1*/if((origen = open(argv[1], O_RDONLY))==-1){

		perror (argv[1]);
		exit (-1);
	}
	if ((destino=open (argv[2], O_WRONLY| O_TRUNC | O_CREAT, 0666))==-1){
		perror (argv[2]);
		exit(-1);
	}

	int i = -1;
	lseek(origen, i, SEEK_END);

	while ((nbytes=read(origen, buffer, sizeof buffer))>0){
		write (destino, buffer, nbytes);
		i--;
		lseek(origen, i, SEEK_END);
		if(lseek(origen, i, SEEK_END) == lseek(origen, -1, SEEK_SET))
			break;

	}
	

	close (destino);
	close(origen);
	exit (0);
	return 0;
}