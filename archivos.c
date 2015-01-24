#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char buffer [BUFSIZ];

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
/*2*/while ((nbytes=read(origen, buffer, sizeof buffer))>0)
/*3*/	write (destino, buffer, nbytes);
/*4*/close (destino);
	close(origen);
	exit (0);
	return 0;
}