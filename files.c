#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define bloque 4097

int main(int argc, char const *argv[])
{
	int fd;
	char arreglo[bloque];
	int j = 0;

	while(j < bloque){
		arreglo[j] = 'a';
		j++;
	}
	
	fd = open(argv[1], O_WRONLY|O_CREAT, 0666); 
	for(j=0;j<1;j++){//este for escribe k bloques en el archivo
		write(fd, arreglo, bloque);
	}
	

	//close (destino);
	close(fd);
	exit (0);
	return 0;
}