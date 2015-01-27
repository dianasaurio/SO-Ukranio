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

/***************************************************FUNCIONES****************************************************/

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
	return files - 2;//no contamos . y ..
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

	if((origen = open("/proc/cpuinfo", O_RDONLY)) == -1){
		perror ("/proc/cpuinfo");
		return -1;
	}

	while ((nbytes=read(origen, buffer, sizeof buffer)) > 0){
		if(strstr(buffer, "processor"))
			cores++;
	}

	close(origen);
	return cores;

}

int buscaCaracter(char letra, char *nombreArchivo, char *directorio){//Esta función busca un caracter en un archivo

	int encontrados = 0;
	char buffer[1];
	int origen;
	int nbytes;
	char file[strlen(nombreArchivo)+strlen(directorio)+1];

	if(directorio[strlen(directorio)-1] != '/')
		sprintf(file, "%s/%s", directorio, nombreArchivo);
	else 
		sprintf(file, "%s%s", directorio, nombreArchivo);	

	if((origen = open(file, O_RDONLY)) == -1){
		perror (file);
		return -1;
	}

	while ((nbytes=read(origen, buffer, sizeof buffer)) > 0){
		if(buffer[0] == letra)	
			encontrados++;
	}

	close(origen);


	return encontrados;

}

void imprimeEspacios(int n){//Sólo para imprimir más bonito
	int i;
	for(i=0;i<n;i++)
		printf(" ");
}



/****************************************************************************************************************/

int main(int argc, char *argv[]){
	
	int files = cuentaArchivos(argv[1]);
	printf("\nSe encontraron %d archivos en el directorio %s\n",files, argv[1]);
	
	char **archivos = obtenArchivos(files, argv[1]);
	int i = 0;
	int j;
	int k;
	int cores;
	int n;
	char letra = argv[2][0];
	pid_t pid;
	int estado;

	cores = Cores();
	n = files / cores; //Cuántos archivos va a analizar cada proceso

	printf("Se encontraron %d nucleos.\n\n", cores);

	/*No hacer mucho caso a esto, sólo es para imprimir guapetón*/

	int max = 0;
	while(archivos[i]){
		if(strlen(archivos[i]) > max)
			max = strlen(archivos[i]);
		i++;
	}

	printf("ARCHIVO");
	imprimeEspacios((max + 8) - 7);
	printf("PID\t   NO. CARACTERES '%c' encontrados\n", letra);

	/************************************************************/

	//Vamos a crear los core proceso y con ello dividir el trabajo para cada uno

	for(j = 1; j < cores; j++){
		pid = fork();
		if(pid != 0)
			break;
	}

	if(pid > 0)
		wait(&estado);

	int inicio;
	int fin;

	if(j == cores){ // Le tocan los últimos archivos, por si el numero de archivos no es exactamente divisible entre los núcleos
		inicio = (j - 1) * n;
		//fin va a ser igual al fin del arreglo, ya que es la última parte
		while(archivos[inicio] != NULL){
			printf("%s", archivos[inicio]);
			imprimeEspacios((max + 8) - strlen(archivos[inicio]));
			printf("%d\t\t\t%d\n", getpid(), buscaCaracter(letra, archivos[inicio], argv[1]));
			inicio++;
		}
		exit(0);

	}else{//Vamos a abrir los archivos del arreglo que le tocan a cada proceso
		inicio = (j - 1) * n;
		fin = (j * n) - 1;
		for(k = inicio; k <= fin; k++){
			printf("%s", archivos[k]);
			imprimeEspacios((max + 8) - strlen(archivos[k]));
			printf("%d\t\t\t%d\n", getpid(), buscaCaracter(letra, archivos[k], argv[1]));

		}
		exit(0);

	}

	return 0;
}