// 4MB = 4194304
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // Incluir
#include <time.h>
#include <string.h>
#define bloque 4000 //Explicar que se almacena en bloques en linux
#define billon 1E9

int cuentaDigitos(int n){
	int cta = 0;
	while(n){
		//printf("%d\n",n%10);
		n=n/10;
		cta++;
	}
	return cta;
}

char* numCadena(int n){
	int i = cuentaDigitos(n);
	char* numero = (char*)malloc(i);
	int j=i-1;
	while(n){
		numero[j--] = n%10 + '0';
		n = n / 10;
	}
	numero[i] = '\0';
	return numero;
}



int main(int argc, char* argv[]){

	struct timespec tiempo1, tiempo2;
	int segaux;
	long nanoaux;
	double tTotal, tBloque, tPromedio = 0;

	char arreglo[bloque];
	int j = 0, size = 4, digitos = 1, k=1, i;
	int fd; 

	while(j < bloque){
		arreglo[j] = 0x40;
		j++;
	}
	arreglo[j-1]='\n';

	
	int n = atoi(argv[1]);
	i=1;

	char archivo[10];

	int inc = 4;

	printf("Tamaño del bloque = 4KB\n");
	printf("Archivo  Tamaño(KB)  Tiempo(S)   Tiempo/Bloque(S)\n");

	while(size<=n){//mientras que los tamaños calculados no sobrepasen a la entrada del usuario
		k = size/4;//numero de bloques que se van a escribir en el archivo

		strcpy(archivo, numCadena(i));//genero el nombre del archivo
		strcat(archivo,".txt");

		clock_gettime(CLOCK_REALTIME, &tiempo1);
		fd = open(archivo, O_WRONLY|O_CREAT, 0666); 
		for(j=0;j<k;j++){//este for escribe k bloques en el archivo
			write(fd, arreglo, bloque);
		}
		sync();
		close(fd); 
		clock_gettime(CLOCK_REALTIME, &tiempo2);

		//Calculamos tiempo de archivo y de bloque

		if(tiempo2.tv_nsec < tiempo1.tv_nsec){
			segaux=(int)tiempo2.tv_sec - (int)tiempo1.tv_sec - 1;
			nanoaux = tiempo1.tv_nsec - tiempo2.tv_nsec;
		}else{
			segaux=(int)tiempo2.tv_sec - (int)tiempo1.tv_sec;
			nanoaux = tiempo2.tv_nsec - tiempo1.tv_nsec;
		}
		tTotal = segaux + nanoaux/billon;
		tBloque = tTotal / k;
		tPromedio += tBloque;

		i++;
		printf("%s\t   %d\t       %0.4lf\t   %lf\n", archivo, size, tTotal, tBloque);
		size += inc;

		if(cuentaDigitos(size)>digitos){
			digitos = cuentaDigitos(size);
			inc = size;
		}

	}
	printf("Tiempo/Bloque(S) promedio = %0.4lf\n", tPromedio / (i-1));
	

	

}