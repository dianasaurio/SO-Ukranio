#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cuentaCaracteres(char* cadena){
	int i = 0;

	while(cadena[i] != NULL){
		i++;
	}
	return i;
}

int main(int argc, char *argv[]){
	
	int tokens;


	/*for(tokens = 0; tokens < argc; tokens++){
		if(argv[tokens][0] == '-')
			printf("Opcion: %s \n", argv[tokens] + 1);
		else
			printf("Argumento %d: %s\n", tokens, argv[tokens]);
	}*/

	tokens = 0;
	while(argv[tokens] != NULL){
		if(argv[tokens][0] == '-'){
			printf("Opcion: %s, Caracteres: %d \n", argv[tokens] + 1, cuentaCaracteres(*(argv + tokens)));
		}
		else{
			printf("Argumento %d: %s, caracteres: %d\n", tokens, argv[tokens], cuentaCaracteres(*(argv + tokens)));
		}
		tokens++;
	}


	exit(0);
}