#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>
#include <time.h>

#define MAX 23500

void funcion(int pid){
	int cuentaS = 500;
	int cuentaC = 500;
	int i = 0;
	int seno;
	int coseno;
	int tangente;
	int logaritmo;
	int raiz;
	int j;
	srand(pid);
	int random;
	
	while(cuentaC > 0 && cuentaS > 0){
		random = rand()%2;
		switch(random){
			case 0://sleep
				if(cuentaS>0){
					//printf("%d Estoy en sleep\n",getpid());
					usleep(10);
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
	pid_t pid;

	int random;
	int estado;
	int j;
	//srand(time(NULL));
	
	/*for(j = 0; j < 4; j++){
		pid = fork();
		if(pid == 0)
			break;	

	}

	if(pid > 0){
		wait(&estado);
		//exit(0);
	}
	else{*/
		//funcion(getpid());
		funcion()
		exit(0);
	//}
	
	return 0;
}
