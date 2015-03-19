#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){


	long int pagesize = sysconf(_SC_PAGESIZE);
	long int totalPaginas = sysconf(_SC_PHYS_PAGES);
	long int paginasDisponibles = sysconf(_SC_AVPHYS_PAGES);

	printf("TAMAÑO DE PAGINA: %ld\n", pagesize);
	printf("PAGINAS EN MEMORIA FISICA: %ld\n", totalPaginas);
	printf("PAGINAS EN MEMORIA FISICA DISPONIBLES: %ld\n", paginasDisponibles);

	printf("Memoria total: %lld\n", (long long int)pagesize*totalPaginas);
	printf("Memoria disponible: %lld\n", (long long int)pagesize*paginasDisponibles);
	printf("Memoria en uso: %lld\n", (long long int)pagesize*(totalPaginas - paginasDisponibles));

	return 0;
}