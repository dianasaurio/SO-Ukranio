//
//	Javier Abell�n. 22 Mayo 2002
//	Programa para demostraci�n del uso de sem�foros
//	
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

//
// Esta union hay que definirla o no seg�n el valor de los defines aqui
// indicados.
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
	int i=0;

   //
   // Igual que en cualquier recurso compartido (memoria compartida, semaforos
   // o colas) se obtien una clave a partir de un fichero existente cualquiera
   // y de un entero cualquiera. Todos los procesos que quieran compartir este
   // semaforo, deben usar el mismo fichero y el mismo entero.
   //             
	Clave = ftok ("/bin/ls", 33);
	if (Clave == (key_t)-1)
	{
		//cout << "No puedo conseguir clave de sem�foro" << endl;
		exit(0);
	}

	//
	// Se obtiene un array de semaforos (10 en este caso, aunque solo se usara
	// uno.
	// El IPC_CREAT indica que lo  cree si no lo est� ya
	// el 0600 con permisos de lectura y escritura para el usuario que lance
	// los procesos. Es importante el 0 delante para que se interprete en
	// octal.
	//               
	Id_Semaforo = semget (Clave, 10, 0600 | IPC_CREAT);
	if (Id_Semaforo == -1)
	{
		//cout << "No puedo crear sem�foro" << endl;
		exit (0);
	}

	//
	//	Se inicializa el sem�foro con un valor conocido. Si lo ponemos a 0,
	//	es sem�foro estar� "rojo". Si lo ponemos a 1, estar� "verde".
	//	El 0 de la funci�n semctl es el �ndice del sem�foro que queremos
	//	inicializar dentro del array de 10 que hemos pedido.
	//
	arg.val = 0;
	semctl (Id_Semaforo, 0, SETVAL, &arg);

	//
	//	Para "pasar" por el sem�foro par�ndonos si est� "rojo", debemos rellenar
	//	esta estructura.
	//	sem_num es el indice del sem�foro en el array por el que queremos "pasar"
	//	sem_op es -1 para hacer que el proceso espere al sem�foro.
	//	sem_flg son flags de operaci�n. De momento nos vale un 0.
	//
	Operacion.sem_num = 0;
	Operacion.sem_op = -1;
	Operacion.sem_flg = 0;

	//
	//	Bucle infinito indicando cuando entramos al sem�foro y cu�ndo salimos
	//	de �l.
	//	i hace de contador del n�mero de veces que hemos salido del sem�foro.
	//
	while (1)
	{
		printf("%d Esperando sem�foro\n", i);//cout << i << " Esperando Sem�foro" << endl;
		//
		//	Se hace la espera en el sem�foro. Se le pasa un array de operaciones
		//	y el n�mero de elementos en dicho array. En nuestro caso solo 1.
		//
		semop (Id_Semaforo, &Operacion, 1);
		printf("%d Salgo del semaforo\n", i);//cout << i << " Salgo de Sem�foro " << endl;
		//cout << endl;
		i++;
	}
}
