#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <X11/Xlib.h>
#include <unistd.h>


/*****Definimos estructura de lista dinámica******/

typedef struct elem{
	int dir;
	int tam;
} Elem;

typedef struct Nodo{
	Elem dato;
   	struct Nodo* sig;
}*Lista;


/*************Definición de funciones*************/

Lista vacia();
Lista cons(Elem, Lista);
int esvacia(Lista);
Elem cabeza(Lista);
Lista resto(Lista);
Lista Pega(Lista, Lista);
Lista insord(Elem, Lista);
void ImpElem(Elem);
void Imprime(Lista);
int esmenor(Elem, Elem);
Lista borrar(Lista, Elem);
int NumElem(Lista);

Lista procesos, huecos;

int search(int aux, char op){

	Lista l = vacia();

	if(op == 'h'){
		l = huecos;
	}else l = procesos;

	while(1){
		if(cabeza(l).dir == aux) return 1;
		else if(esvacia(resto(l))) return 0;
		else l = resto(l);
	}
}

int buscaDer(Elem e){ //Regresa un 0 si a la derecha del proceso hay un hueco

	int aux = e.dir + e.tam;
	//primero buscamos en la lista de huecos
	if(search(aux, 'h')) return 1;
	//después buscamos en la lista de procesos
	else if(search(aux, 'p')) return 0;
	else return -1;
}

int buscaIzq(Elem e){ //Regresa un 0 si a la izquierda del proceso hay un hueco

	int i = 1;
	//primero buscamos en la lista de huecos
	while(1){
		if(!search(e.dir-1024*i, 'h')){
			i++;
		}else return 0;
	}
	//después buscamos en la lista de procesos
	i = 1;
	while(1){
		if(!search(e.dir-1024*i, 'p')){
			i++;
		}else return 1;
	}
	return -1;

}

/**************************************************/

int main(){
	Elem aux;
	aux.dir = 4096;
	aux.tam = 60;
	procesos = vacia();
	huecos = vacia();
	int i = 10;
	srand(0);
	//Elem aux;

	aux.tam = 1;

	while(i){
		aux.dir += (rand()%4 + 1)*1024;
		procesos = insord(aux, procesos);
		i--;
	}

	Imprime(procesos);
	puts("");

	aux.dir = 27648;

	if(search(aux.dir,'p'))
		printf("Se encontró\n\n");
	
	Imprime(borrar(procesos, aux));

	/*if(search(aux.dir,'p'))
		printf("Se encontró\n\n");*/

	//Imprime(procesos);
	//Elem x = cabeza(procesos);
	//ImpElem(x);

	return 0;
}

/*******************Funciones de manipulación de estructura Lista*******************/

/************************************************************
 * NOTA: La implementación que utilizo de una lista ligada  *
 * dinámica es de mi curso de  estructuras de datos con el  *
 * profesor Santiago Suárez Castañón. No es plagio! ):      *
 *                                                          *
 ************************************************************/

Lista vacia(){return NULL;}

Lista cons(Elem e, Lista l){
	Lista temp =(Lista) malloc (sizeof(struct Nodo));
	temp->dato=e;//mete el valor de dato del nodo al que apunta temp
	temp->sig=l;
    return temp;
}

int esvacia(Lista l){return l==NULL;}

Elem cabeza(Lista l){return l->dato;}

Lista resto(Lista l){return l->sig;}

Lista Pega(Lista l1, Lista l2){

	if(esvacia(l1))
		return l2;
	else if(esvacia(l2))
			return l1;
		 else if ((esvacia(l1))&&(esvacia(l2)))
		 		return l1;
		 	  else{
		 	  	return cons(cabeza(l1),Pega(resto(l1),l2));
		 	  }
}

Lista insord(Elem e, Lista l){

	if(esvacia(l))
		return cons(e,vacia());
	else if(esmenor(e,cabeza(l)))
			return cons(e,l);
		 else 
		 	return cons(cabeza(l),insord(e,resto(l)));

}

void ImpElem(Elem e){
	printf("|dir: %d|tam: %dK|\n",e.dir, e.tam);
	return;
}

void Imprime(Lista l){
	if(!esvacia(l)){
		ImpElem(cabeza(l));
		Imprime(resto(l));
	}
	return;
}	

int esmenor(Elem e1, Elem e2){
	if(e1.dir < e2.dir)
		return 1;
	else
		return 0;
}	

Lista borrar(Lista l, Elem e){

	Lista aux;
	aux = vacia();
	int i = 0;
	while(1){
		if(cabeza(l).dir != e.dir){
			aux = insord(cabeza(l), aux);
			l = resto(l);
		}else break;
	}
	l = resto(l);

	return Pega(aux, l);
}

int NumElem(Lista l){
	if(!esvacia(l))
		return 1+NumElem(resto(l));
	else return 0;
}
