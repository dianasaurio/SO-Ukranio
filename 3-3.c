#include <stdlib.h>
#include <stdio.h>

extern char **environ;

int main(int arcg, char *argv[]){

	int i;
	/*printf("Las variables de entorno para %s son\n", argv[0]);
	for (i = 0; environ[i] != NULL; i++){
		printf("environ[%d] = %s\n", i, environ[i]);
	}*/

	printf("%s\n", getenv("HOME"));

	return 0;
}

