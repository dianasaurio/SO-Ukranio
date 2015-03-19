#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>
#include <time.h>

#define MAX 23500

void funcion(){
	int cuentaS = 500;
	int cuentaC = 1000;
	int i = 0;
	int seno;
	int coseno;
	int tangente;
	int logaritmo;
	int raiz;
	int j;
	int random;
	srand(time(NULL));
	
	while(cuentaC > 0 && cuentaS > 0){
		
		random = rand()%2;
		switch(random){
			case 0://sleep
				if(cuentaS>0){
					//printf("%d Estoy en sleep\n",getpid());
					usleep(10000);
					cuentaS--;
				}
				break;
			case 1://calculos
				if(cuentaC>0){
					//printf("%d Estoy haciendo calculos\n",getpid());
					while(i<MAX){
						seno += sin(i);
						coseno += cos(i);
						tangente += tan(i);
						logaritmo += log(i);
						raiz += sqrt(i);
						i++;
					}
					i = 0;
					cuentaC--;
				}	
				break;
		}
	}

}

int main(){

	int random;
	int estado;
	int j;

	funcion();
	//funcion();

	return 0;
}
