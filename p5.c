// 4MB = 4194304
#include <fcntl.h> // Incluir
#include <time.h>
#define tamanio 1 //Explicar que se almacena en bloques en linux
void main(void){

	struct timespec tiempo1, tiempo2;
	int segaux;
	long nanoaux;

	char arreglo[tamanio];
	int j = 0;
	int fd; //

	while(j < tamanio){
		arreglo[j] = 0x40;
		j++;
	}

	clock_gettime(CLOCK_REALTIME, &tiempo1);

	fd = open("/media/dianasaurio/HRM_CCSA_X6/archivo.txt", O_WRONLY|O_CREAT, 0666); //
	write(fd, arreglo, tamanio); //
	//sync(); // al ultimo
	close(fd); //

	clock_gettime(CLOCK_REALTIME, &tiempo2);

	if(tiempo2.tv_nsec < tiempo1.tv_nsec){
		segaux=(int)tiempo2.tv_sec - (int)tiempo1.tv_sec - 1;
		nanoaux = tiempo1.tv_nsec - tiempo2.tv_nsec;
	}else{
		segaux=(int)tiempo2.tv_sec - (int)tiempo1.tv_sec;
		nanoaux = tiempo2.tv_nsec - tiempo1.tv_nsec;
	}
	printf("Segundos: %d\n", segaux);
	printf("Nanosegundos: %ld\n", nanoaux);

}