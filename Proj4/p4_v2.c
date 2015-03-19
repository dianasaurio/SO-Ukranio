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
	int flag;
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
Lista RAM;
int ppix = 22;
int hpix = 22;

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
Lista borrar(Elem);

char *itoa(int);
void dibujaRam();
void muestraPantalla();
void dibujaLista();
void limpiaRam();
void killProcess(Elem);
int buscaDer(Elem);
int buscaIzq(Elem);
Elem regresaIzquierdo(Elem);
Elem regresaDerecho(Elem);
void addProcess(int);
Elem search(int);
int NumProc();
void escribeLista();
void dibujaPix(int);
void borraPix(int);

/***********************************************/

int main(){

	procesos = vacia();
	Elem aux;
	aux.dir = 4096;
	aux.tam = 60;
	huecos = vacia();//cons(aux, huecos);
	RAM = vacia();
	int opcion;
	int n;
	int Plen;
	int Hlen;
	int paux;

	srand(time(NULL));

	muestraPantalla();
	dibujaRam();


	aux.dir = 4096;
	aux.tam = 60;
	aux.flag = 0;

	RAM = cons(aux, RAM);
	dibujaPix(0);

	while(1){	

		opcion = rand()%2;

		if(opcion){ //Agregar proceso
			paux = rand()%5 + 1;
			printf("Agregando proceso de %dK...\n",paux);
			addProcess(paux);
			//Imprime(RAM);
			limpiaRam();
			dibujaLista();
			escribeLista();
			sleep(1);

		}else{ //Matar proceso

			Plen = NumProc(RAM);
			if(Plen > 1){
				n = rand()%Plen + 1;//Elegimos un proceso random de la lista para matar
				printf("Finalizando proceso %d...\n", n);
				killProcess(search(n));
				//Imprime(RAM);
				limpiaRam();
				dibujaLista();
				escribeLista();
				sleep(1);

			}

		}

	}

	return 0;
}

/****************************************Funciones*********************************/

void addProcess(int size){//Algoritmo utilizado: Primer ajuste

	Lista aux = vacia();
	aux = RAM;
	Elem hueco;
	Elem huecoRestante;
	Elem proceso;

	while(1){
		 if(cabeza(aux).flag == 0){
		 	if(cabeza(aux).tam >= size){
			 	hueco = cabeza(aux);//el hueco que encontramos
			 	proceso.dir = hueco.dir;
			 	proceso.tam = size;
			 	proceso.flag = 1;
			 	huecoRestante.dir = hueco.dir + proceso.tam*1024;
			 	huecoRestante.tam = hueco.tam - proceso.tam;
			 	huecoRestante.flag = 0;
			 	RAM =  borrar(hueco);
			 	RAM = insord(proceso, RAM);
			 	dibujaPix(1);
			 	if(huecoRestante.tam > 0){
			 		RAM = insord(huecoRestante, RAM);
					//dibujaPix(0);

			 	}else{
			 		borraPix(0);
			 	}
			 	return;

			 }else if(esvacia(resto(aux))){
			 	printf("No hay espacio suficiente ): \n");
			 	return;
			 }else{
			 	aux = resto(aux);
			 }
		}else if(!esvacia(resto(aux))) aux = resto(aux);
		else{
			printf("No hay espacio suficiente ): \n");
			return;
		}
	}

}

void killProcess(Elem e){

	Elem aux, izq, der;

	izq = regresaIzquierdo(e);
	der = regresaDerecho(e);

	if(izq.flag == 0 &&  der.flag== 0){ //H P H
		RAM = borrar(e);				
		RAM = borrar(der);
		RAM = borrar(izq);
		borraPix(0);
		borraPix(1);
		aux.dir = izq.dir;
		aux.tam = e.tam + izq.tam + der.tam;
		aux.flag = 0;
		RAM = insord(aux, RAM);

	}

	if(izq.flag == 1 && der.flag == 0){// P P H

		RAM = borrar(e);
		RAM = borrar(der);
		borraPix(1);
		aux.dir = e.dir;
		aux.tam = e.tam + der.tam;
		aux.flag = 0;
		RAM = insord(aux, RAM);
		
	}

	if(izq.flag == 0 && der.flag == 1){// H P P

		RAM = borrar(e);
		RAM = borrar(izq);
		borraPix(1);
		aux.dir = izq.dir;
		aux.tam = e.tam + izq.tam;
		aux.flag = 0;
		RAM = insord(aux, RAM);

	}	

	if(izq.flag == 1 && der.flag == 1){ //P P P
		RAM = borrar(e);
		borraPix(1);
		dibujaPix(0);
		e.flag = 0;
		RAM = insord(e, RAM);
	}

	if(izq.flag == 0 && der.flag == -1){ //H P -1

		RAM = borrar(e);
		RAM = borrar(izq);
		borraPix(1);
		aux.dir = izq.dir;
		aux.tam = e.tam + izq.tam;
		aux.flag = 0;
		RAM = insord(aux, RAM);

	}

	if(izq.flag == 1 && der.flag == -1){ //P P -1

		dibujaPix(0);
		borraPix(1);
		RAM = borrar(e);
		e.flag = 0;
		RAM = insord(e, RAM);

	}

	if(izq.flag == -1 && der.flag == 0){ //-1 P H
		RAM = borrar(e);
		RAM = borrar(der);
		borraPix(1);

		aux.dir = e.dir;
		aux.tam = e.tam + der.tam;
		aux.flag = 0;
		RAM = insord(aux, RAM);
	}

	if(izq.flag == -1 && der.flag == 1){ //-1 P P

		RAM = borrar(e);
		e.flag = 0;
		borraPix(1);
		dibujaPix(0);
		RAM = insord(e, RAM);
	}

	return;
	
}

Elem search(int n){

	Lista l = vacia();
	l = RAM;
	int i = 0;
	Elem e;

	while(!esvacia(l)){
		if(cabeza(l).flag == 1 && i < n){
			i++;
			e = cabeza(l);
			l = resto(l);

		}else if(cabeza(l).flag == 0){
			l = resto(l);
		}else break;
		
	}
	//puts("");
	//ImpElem(e);
	//puts("");
	return e;
}

Elem regresaIzquierdo(Elem e){//nota: validar que no esté en los extremos
	Lista l = vacia();
	l = RAM;

	if(e.dir == cabeza(l).dir){
		Elem x;
		x.dir = -1;
		x.tam = -1;
		x.flag = -1;
		return x;
	}

	Elem izquierdo = cabeza(l);
	l = resto(l);

	while(izquierdo.dir < e.dir){
		if(cabeza(l).dir==e.dir){
			return izquierdo;
		}else{
			izquierdo = cabeza(l);
			l = resto(l);
		}
	}
}

Elem regresaDerecho(Elem e){

	int aux = e.dir+e.tam*1024;
	Lista l = vacia();
	l = RAM;
	while(1){
		if(cabeza(l).dir == aux)
			return cabeza(l);
		else{
			l = resto(l);
		}if(esvacia(l)){
			Elem x;
			x.dir = -1;
			x.tam = -1;
			x.flag = -1;
			return x;
		}
	}

}

void dibujaPix(int op){
	color.red = 65535;
	color.blue = 65535;
	color.green = 65535;
	XAllocColor(disp, DefaultColormap(disp, DefaultScreen(disp)), &color);
	XSetForeground(disp, XDefaultGC(disp, DefaultScreen(disp)), color.pixel);

	if(op){//procesos
		XDrawPoint(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), ppix, 80);
		ppix++;
	}else{//huecos
		XDrawPoint(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), hpix, 90);
		hpix++;
	}
	XFlush(disp);
	return;


}

void borraPix(int op){
	color.red = 0;
	color.blue = 65535;
	color.green = 0;
	XAllocColor(disp, DefaultColormap(disp, DefaultScreen(disp)), &color);
	XSetForeground(disp, XDefaultGC(disp, DefaultScreen(disp)), color.pixel);

	if(op){//procesos
		ppix--;
		XDrawPoint(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), ppix, 80);
	}else{//huecos
		hpix--;
		XDrawPoint(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), hpix, 90);
	}
	XFlush(disp);
	return;	
}

void escribeLista(){
	Lista l = vacia();
	l = RAM;
	int offset = 10, offset2 = 10;
	int i = 8;
	int k = 8;
	char buffer [50];
	int n;
	int y = 150;
	int y2 = 280;
	Elem c;

	XClearArea(disp, ventana, 9, 120, 1200, 500, 1);
	XFlush(disp);

	color.red = 65535;
	color.blue = 65535;
	color.green = 65535;
	XAllocColor(disp, DefaultColormap(disp, DefaultScreen(disp)), &color);
	XSetForeground(disp, XDefaultGC(disp, DefaultScreen(disp)), color.pixel);
	XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), 12, 140, "PROCESOS", 8);
	XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), 12, 270, "HUECOS", 6);
	XFlush(disp);

	color.red = 0;
	color.blue = 0;
	color.green = 65535;
	XAllocColor(disp, DefaultColormap(disp, DefaultScreen(disp)), &color);
	XSetForeground(disp, XDefaultGC(disp, DefaultScreen(disp)), color.pixel);

	while(!esvacia(l)){
		c = cabeza(l);
		
		if(c.flag){
			n = sprintf (buffer, "|%#.4x|%dK|%#.4x|->", c.dir, c.tam, k);
			k = k + 8;
			XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), offset, y, buffer, n);
			offset = offset + 15*8;
			if(offset > 1200){
				offset = 10;
				y = y + 16;
			}
		}else{
			n = sprintf (buffer, "|%#.4x|%dK|%#.4x|->", c.dir, c.tam, i);
			i = i + 8;
			XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), offset2, y2, buffer, n);
			offset2 = offset2 + 15*8;
			if(offset2 > 1200){
				offset2 = 10;
				y2 = y2 + 16;
			}
		}

		l = resto(l);
	}
	XFlush(disp);
}

void dibujaLista(){

	Lista x = vacia();
	x =  RAM;
	Elem c = cabeza(x);
	int offset = 90;

			
	while(!esvacia(x)){
		c = cabeza(x);

		if(!c.flag){
			offset = offset + c.tam*20;
			color.red = 65535;
			color.blue = 65535;
			color.green = 65535;
			XAllocColor(disp, DefaultColormap(disp, DefaultScreen(disp)), &color);
			XSetForeground(disp, XDefaultGC(disp, DefaultScreen(disp)), color.pixel);
			XDrawLine(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), offset, 10, offset, 100);
			XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), offset - c.tam*10, 59, itoa(c.tam), strlen(itoa(c.tam)));
			XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), offset - c.tam*10, 70, "K", 1);
			XFlush(disp);
			
		}else{

			color.red = 65535;
			color.blue = 65535;
			color.green = 65535;

			XAllocColor(disp, DefaultColormap(disp, DefaultScreen(disp)), &color);
			XSetForeground(disp, XDefaultGC(disp, DefaultScreen(disp)), color.pixel);
			XFillRectangle(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), offset, 11, c.tam * 20, 90);
			color.red = 0;
			color.blue = 0;
			color.green = 0;
			XAllocColor(disp, DefaultColormap(disp, DefaultScreen(disp)), &color);
			XSetForeground(disp, XDefaultGC(disp, DefaultScreen(disp)), color.pixel);
			XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), offset + c.tam*10, 59, itoa(c.tam), strlen(itoa(c.tam)));
			XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), offset + c.tam*10, 70, "K", 1);
			XDrawLine(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), offset, 11, offset, 99);
			offset = offset + c.tam*20;
			XFlush(disp);
			

		}	
		x = resto(x);

	}

	return;
}

void limpiaRam(){

	XClearArea(disp, ventana, 91, 11, 1199, 89, 1);
	XFlush(disp);
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
	XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), 12, 80, "P", 1);
	XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), 12, 90, "H", 1);

	XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), 12, 140, "PROCESOS", 8);
	XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), 12, 270, "HUECOS", 6);

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
	printf("|dir: %d|tam: %dK|f:%d|\n",e.dir, e.tam, e.flag);
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

Lista borrar(Elem e){

	Lista aux;
	aux = vacia();

	//puts("Cabezas de borrar h");
	while(1){
		//ImpElem(cabeza(huecos));
		if(cabeza(RAM).dir != e.dir){
			aux = insord(cabeza(RAM), aux);
			RAM = resto(RAM);
		}else break;
	}
	RAM = resto(RAM);
	return Pega(aux, RAM);

}

int NumProc(){
	Lista l = vacia();
	l = RAM;
	int i = 0;
	while(!esvacia(l)){
		if(cabeza(l).flag){
			i++;
		}
		l = resto(l);
	}
	return i;
}
