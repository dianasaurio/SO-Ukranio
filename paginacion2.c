#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){

	int i = 4096;
	printf("ID de proces: %d\n", getpid());
	while(1){
		memset(malloc(i), 'a', i);
		printf("Paginas disponibles: %ld\n", sysconf(_SC_AVPHYS_PAGES));
		i = i + 4096;
		//sleep(1);
	}
	pause();


	return 0;
}