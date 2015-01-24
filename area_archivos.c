#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>

double Area(double inicio, double fin, double delta){

	double area = 0.0000000000000000f;
	double y;
	double temp;
	double i;


	for(i=inicio;i<fin;i=i+delta){
		y = sqrt(1-(i)*(i));
		temp = delta*y;
		area += temp;
	}
	return area;
}

int main(int argc, char *argv[]){

	int n = atoi(argv[1]);
	int estado;
	double inicio, fin;
	double delta = 1.0 / n;
	
	pid_t pid;
	int j;
	
	printf("pi = %.16lff\n", acos(-1));
	//Vamos a crear 4 procesos, uno para cada nucleo
	for(j = 0; j < 4; j++){
		pid = fork();
		if(pid == 0)
			break;	
	}
	
	switch(j){
		case 0:
			wait(&estado);
		case 1:
			inicio = delta;
			fin = 0.25;
			break;
		case 2:
			inicio = 0.25;
			fin = 0.5;
			break;
		case 3:
			inicio = 0.5;
			fin = 0.75;
			break;
		case 4:
			inicio = 0.75;
			fin = 1.0;
			break;
	}
	
	File* archivo;
	//printf("Area de proceso %d, hijo de %d: %.16lff\n", getpid(), getppid(), Area(inicio, fin, delta)*4);
	fprintf(archivo, );
	exit(0);


	return 0;
}