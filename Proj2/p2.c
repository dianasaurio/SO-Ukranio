/****************************************
*										*
* Proyecto 2 							*
* Sistemas Operativos					*
* Profesor: Ukranio Contreras			*
* Alumna: Sánchez Urbán Diana Pamela	*
* Grupo: 2CM4							*
*										*
*****************************************/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

/*****************FUNCIONES******************/

int cuentaArchivos(char* directorio){ 
/* Esta función recibe el directorio y retorna cuántos archivos existen en dicho directorio*/
	DIR *dip;
	struct dirent *dit;
	int files = 0;

	if((dip = opendir(directorio)) == NULL){
		perror("opendir");
		return -1;
	}

	while ((dit = readdir(dip)) != NULL){
		files++;
	}

	if (closedir(dip) == -1){
		perror("closedir");
		return -1;
	}
	return files;//no contamos . y ..
}

char **obtenArchivos(int n, char* directorio){
/* Esta función recibe el número de archivos que hay en un directorio, el directorio
 * y retorna arreglo de cadenas con los nombres de todos los archivos, quitando . y ..
 */

	DIR *dip;
	struct dirent *dit;
	int i = 0;

	//creando un arreglo para guardar los nombres de los archivos
	char **archivos = malloc(sizeof(char*)*(n+1));

	if((dip = opendir(directorio)) == NULL){
		perror("opendir");
	}

	while ((dit = readdir(dip)) != NULL){

		if(((strcmp(dit->d_name, ".")) && (strcmp(dit->d_name, "..")))){ //Quitamos . y ..
			archivos[i] = malloc(sizeof(char)*(strlen(dit->d_name)+1));
			archivos[i][(strlen(dit->d_name)+1)] = '\0';
			strcpy(archivos[i++], dit->d_name);
		}

	}
	archivos[i] = NULL;

	if (closedir(dip) == -1){
		perror("closedir");
	}
	return archivos;
}

int Cores(){ //Esta función cuenta el número de nucleos para la computadora
	
	char buffer[100];
	int origen;
	int nbytes;
	int cores = 0;

	if((origen = open("/proc/cpuinfo", O_RDONLY))==-1){
		perror ("/proc/cpuinfo");
		return -1;
	}

	while ((nbytes=read(origen, buffer, sizeof buffer))>0){
		if(strstr(buffer, "processor"))
			cores++;
	}

	close(origen);
	return cores;

}



/**********************************************/

int main(int argc, char *argv[]){
	
	int files = cuentaArchivos(argv[1]);()
	//printf("Archivos en el directorio:%d \n",files);
	
	char **archivos = obtenArchivos(files, argv[1]);
	int i = 1;
	int j;
	int cores;
	int n;

	/*while(*archivos) {
	    printf("file %d: %s, len: %d\n", i++, *archivos, strlen(*archivos));
	    archivos++;
  	}*/

	cores = Cores();
	printf("Se encontraron %d nucleos.\n", cores);

	n = files / cores; //Cuántos archivos va a analizar cada proceso

	//Vamos a crear los core proceso y con ello dividir el trabajo para cada uno

	for(j = 1; j <= cores; j++){
		pid = fork();
		if(pid == 0)
			break;	
	}

	switch(j){
		case cores: // Le tocan los últimos archivos, por si el 
			break;
		default : 
			//Vamos a abrir los archivos de 
			break;

	}
	
	

	return 0;
}

