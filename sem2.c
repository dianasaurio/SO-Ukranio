//
// Javier Abell�n, 23 Mayo 2002
// Programa de demostraci�n de sem�foros.
//
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


//
//	Esta union hay que definirla o no seg�n el valor de los defines aqui
//	indicados.
//	
#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
// La union ya est� definida en sys/sem.h
#else
// Tenemos que definir la union
union semun 
{ 
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};
#endif

main()
{
	key_t Clave;
	int Id_Semaforo;
	struct sembuf Operacion;
	union semun arg;
	int i;

	//
	//	Igual que en cualquier recurso compartido (memoria compartida, semaforos
	//	o colas) se obtien una clave a partir de un fichero existente cualquiera
	//	y de un entero cualquiera. Todos los procesos que quieran compartir este
	// semaforo, deben usar el mismo fichero y el mismo entero.
	//
	Clave = ftok ("/bin/ls", 33);
	if (Clave == (key_t)-1)
	{
		//cout << "No puedo conseguir clave de sem�foro" << endl;
		exit(0);
	}

	//
	//	Se obtiene un array de semaforos (10 en este caso, aunque solo se usara
	//	uno.
	//	El IPC_CREAT indica que lo  cree si no lo est� ya 
	//	el 0600 con permisos de lectura y escritura para el usuario que lance 
	//	los procesos. Es importante el 0 delante para que se interprete en
	//	octal.
	//	
	Id_Semaforo = semget (Clave, 10, 0600 | IPC_CREAT);
	if (Id_Semaforo == -1)
	{
		//cout << "No puedo crear sem�foro" << endl;
		exit (0);
	}

	//
	//	Se levanta el sem�foro. Para ello se prepara una estructura en la que
	//	sem_num indica el indice del semaforo que queremos levantar en el array
	//	de semaforos obtenido.
	//	El 1 indica que se levanta el semaforo 
	//	El sem_flg son banderas para operaciones raras. Con un 0 vale.
	//
	Operacion.sem_num = 0;
	Operacion.sem_op = 1;
	Operacion.sem_flg = 0;

	//
	//	Vamos a levantar el sem�foro 10 veces esperando 1 segundo cada vez.
	//
	for (i = 0; i<10; i++)
	{
		printf("Levanto semaforo\n");//cout << "Levanto Sem�foro" << endl;
		//
		// Se realiza la operaci�n de levantar el sem�foro. Se pasa un array
		// de Operacion y el n�mero de elementos en el array de Operacion. En
		// nuestro caso solo 1.
		//
		semop (Id_Semaforo, &Operacion, 1);
		sleep (1);
	}
}
