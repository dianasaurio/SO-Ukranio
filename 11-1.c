#include <stdio.h>
#include <signal.h>

void tratar_alarma(int a){
	printf("Alarma activada, %d \n", a);
}

int main(){
	struct sigaction act;
	sigset_t mask;

	/*Especifica el manejador*/

	act.sa_handler = tratar_alarma; /*funcion a ejecutar*/
	act.sa_flags = 0; /*NInguna accion especifica*/

	/*se bloquea la señal 3 SIGInT*/
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGALRM);
	sigprocmask(SIG_SETMASK, &mask, NULL);

	sigaction(SIGALRM, &act, NULL);

	for(;;){
		alarm(10);//ualarm(500000,500000); /*se arma el temporizador*/
		pause();/*se suspende el proceso hasta que se reciba la señal*/
	}

	return 0;
}