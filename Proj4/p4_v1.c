/****************************************
*										*
* Proyecto 4 							*
* Sistemas Operativos					*
* Profesor: Ukranio Contreras			*
* Alumna: Sánchez Urbán Diana Pamela	*
* Grupo: 2CM4							*
*										*
*****************************************/
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

/****************Variables globales***************/

Display *disp = NULL;
Window ventana;
XColor color;
Lista huecos;
Lista procesos;

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
Lista borrar(char, Elem);
int NumElem(Lista);


char *itoa(int);
void dibujaRam();
void muestraPantalla();
void dibujaListas();
void limpiaRam();
void killProcess(Elem);
int buscaDer(Elem);
int buscaIzq(Elem);
int search(int aux, char op);
Elem regresaIzquierdo(char, Elem);
Elem regresaDerecho(char, Elem);

/***********************************************/

int main(){

	procesos = vacia();
	Elem aux;
	aux.dir = 4096;
	aux.tam = 60;
	huecos = vacia();//cons(aux, huecos);
	int opcion;
	int n;
	int Plen;
	int Hlen;

	srand(time(NULL));

	/*muestraPantalla();
	dibujaRam();

	while(1){

		opcion = rand()%2;

		if(opcion){ //Agregar proceso



		}else{ //Matar proceso

			Plen = NumElem(procesos);
			if(Plen > 0){
				n = rand()%n + 1;//Elegimos un proceso random de la lista para matar


			}

		}

	}*/

	aux.dir = 4049;
	aux.tam = 1;
	procesos = insord(aux, procesos);
	aux.dir = 5192;
	aux.tam = 1;
	procesos = insord(aux, procesos);
	aux.dir = 9216;
	aux.tam = 2;
	procesos = insord(aux, procesos);
	aux.dir = 13312;
	aux.tam = 1;
	procesos = insord(aux, procesos);
	aux.dir = 16384;
	aux.tam = 3;
	procesos = insord(aux, procesos);
	aux.dir = 21504;
	aux.tam = 2;
	procesos = insord(aux, procesos);
	aux.dir = 23552;
	aux.tam = 2;
	procesos = insord(aux, procesos);

	aux.dir = 5120;
	aux.tam = 3;
	huecos = insord(aux, huecos);
	aux.dir = 11264;
	aux.tam = 2;
	huecos = insord(aux, huecos);
	aux.dir = 19456;
	aux.tam = 2;
	huecos = insord(aux, huecos);
	aux.dir = 14336;
	aux.tam = 2;
	huecos = insord(aux, huecos);
	aux.dir = 25600;
	aux.tam = 2;
	huecos = insord(aux, huecos);

	Imprime(huecos);
	puts("");
	Imprime(procesos);

	aux.dir = 9216;
	aux.tam = 2;


	if(buscaIzq(aux) == 0) puts("Hay un hueco a la izquierda");
	else if(buscaIzq(aux) == 1)puts("Hay un proceso a la izquierda");
	else puts("error");

	if(buscaDer(aux) == 0) puts("Hay un hueco a la derecha");
	else if(buscaDer(aux) == 1)puts("Hay un proceso a la izquierda");
	else puts("error");

	killProcess(aux);
	puts("Huecos");
	Imprime(huecos);
	puts("Procesos");
	Imprime(procesos);


	return 0;
}

/****************************************Funciones*********************************/


void killProcess(Elem e){

	puts("killproc");
	Elem aux, izq, der;
	int i = buscaIzq(e);
	int d = buscaDer(e);


	if(i == 0 &&  d== 0){
		
		//puts("caso 1");
		izq = regresaIzquierdo('h', e);
		der = regresaDerecho('h', e);

		/*ImpElem(izq);
		ImpElem(der);
		puts("E a borrar:");
		ImpElem(e);
		puts("");
		Imprime(procesos);
		puts("");*/

		aux.tam = izq.tam + der.tam + e.tam;
		aux.dir = izq.dir;
		procesos = borrar('p',e);
		huecos = borrar('h', izq);
		huecos = borrar('h', der);
		huecos = insord(aux, huecos);

		return;

	}

	if(i == 1 && d == 0){// P P H

		der = regresaDerecho('h', e);
		aux.dir = e.dir;
		aux.tam = e.tam + der.tam;
		procesos = borrar('p',e);
		huecos = borrar('h',der);
		huecos = insord(aux,huecos);
	}

	if(i == 0 && d == 1){// H P P

	}	

	if(i == 1 && d == 1){

	}

	
}

Elem regresaIzquierdo(char op, Elem e){
	puts("regresaIzq");
	Lista l = vacia();

	if(op == 'h'){
		l = huecos;
	}else{
		l = procesos;
	}

	Elem anterior = cabeza(l);

	while(1){
		if(cabeza(l).dir < e.dir){
			anterior = cabeza(l);
			l = resto(l);
		}else return anterior;
	}

}

Elem regresaDerecho(char op, Elem e){
	puts("regresaDer");

	int aux = e.dir+e.tam*1024;
	Lista l = vacia();

	if(op == 'h'){
		l = huecos;
	}else{
		l = procesos;
	}

	while(1){
		if(cabeza(l).dir != aux){
			l = resto(l);
		}else return cabeza(l);
	}
}

int search(int aux, char op){

	Lista l = vacia();

	if(op = 'h'){
		l = huecos;
	}else l = procesos;

	while(1){
		if(cabeza(l).dir  == aux) return 1;
		else if(esvacia(resto(l))) return 0;
		else l = resto(l);
	}
}

int buscaDer(Elem e){ //Regresa un 0 si a la derecha del proceso hay un hueco

	//puts("buscaDer");
	int aux = e.dir + 1024*e.tam;
	//primero buscamos en la lista de huecos
	if(search(aux, 'h')) return 0;
	//después buscamos en la lista de procesos
	else if(search(aux, 'p')) return 1;
	else return -1;
}

int buscaIzq(Elem e){ //Regresa un 0 si a la izquierda del proceso hay un hueco
	//puts("buscaIzq");
	int i = 1;
	int offset;
	offset = e.dir-1024*i;
	//primero buscamos en la lista de huecos
	while(offset >= 4096){
		offset = e.dir-1024*i;
		if(!search(offset, 'h')){
			i++;
		}else return 0;
	}
	//después buscamos en la lista de procesos
	i = 1;
	offset = e.dir-1024*i;
	while(offset >= 4096){
		offset = e.dir-1024*i;
		if(!search(offset, 'p')){
			i++;
		}else return 1;
	}
	return -1;

}


void dibujaListas(){

	return;
}

void limpiaRam(){

	return;
}

char *itoa(int n){

	static char retbuf[25];
	sprintf(retbuf, "%d", n);
	return retbuf;
}

void muestraPantalla(){
	disp = XOpenDisplay(NULL);
	ventana = XCreateSimpleWindow(disp, XDefaultRootWindow(disp), 100, 100, 1320, 500, 1, 1, BlackPixel(disp, DefaultScreen(disp)));

	XMapWindow(disp, ventana);
	XFlush(disp);
	color.flags = DoRed | DoGreen | DoBlue;
	color.red = 65535;
	color.blue = 65535;
	color.green = 65535;
	XAllocColor(disp, DefaultColormap(disp, DefaultScreen(disp)), &color);
	XSetForeground(disp, XDefaultGC(disp, DefaultScreen(disp)), color.pixel);
	return;
}

void dibujaRam(){

	usleep(5000);

	XDrawLine(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), 90, 10, 1290, 10);
	XDrawLine(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), 90, 100, 1290, 100);
	XDrawLine(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), 1290, 10, 1290, 100);
	
	color.red = 0;
	color.blue = 65535;
	color.green = 0;
	XAllocColor(disp, DefaultColormap(disp, DefaultScreen(disp)), &color);
	XSetForeground(disp, XDefaultGC(disp, DefaultScreen(disp)), color.pixel);

	XFillRectangle(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), 10, 10, 80, 91);

	color.red = 65535;
	color.blue = 65535;
	color.green = 65535;
	XAllocColor(disp, DefaultColormap(disp, DefaultScreen(disp)), &color);
	XSetForeground(disp, XDefaultGC(disp, DefaultScreen(disp)), color.pixel);

	XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), 45, 59, "SO", strlen("SO"));
	XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), 45, 70, "4K", strlen("4K"));
	XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), 600, 70, "60K", strlen("60K"));
	XFlush(disp);
	//sleep(100);
	return;
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

Lista borrar(char op, Elem e){

	Lista aux, l;
	aux = vacia();
	int i = 0;

	if(op == 'h'){
		//puts("Cabezas de borrar h");
		while(1){
			//ImpElem(cabeza(huecos));
			if(cabeza(huecos).dir != e.dir){
				aux = insord(cabeza(huecos), aux);
				huecos = resto(huecos);
			}else break;
		}
		huecos = resto(huecos);
		return Pega(aux, huecos);
	}else{
		//puts("Cabezas de borrar p");
		while(1){
			//ImpElem(cabeza(huecos));
			if(cabeza(procesos).dir != e.dir){
				aux = insord(cabeza(procesos), aux);
				procesos = resto(procesos);
			}else break;
		}
		procesos = resto(procesos);
		return Pega(aux, procesos);
	}
}

int NumElem(Lista l){
	if(!esvacia(l))
		return 1+NumElem(resto(l));
	else return 0;
}
