/*compilar con -lX11*/
#include <X11/Xlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Display *disp = NULL;
Window ventana;
XColor color;

char *itoa(int n){

	static char retbuf[25];
	sprintf(retbuf, "%d", n);
	return retbuf;
}

void dibujaRect(int x, int y, int ancho, int largo){
	XFillRectangle(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), x, y, ancho, largo);
	XFlush(disp);
	return;
}

void limpiaHueco(int x, int y, int ancho, int largo){
	XClearArea(disp, ventana, 200, 200, 100, 50, 1);
	XFlush(disp);
}

int main(){
	
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

	//while(1)
	//sleep(1);
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
	XFlush(disp);

	int i, x = 90;
	for(i = 1; i<=60; i++){
		//printf("%d %d\n", i, x);
		XDrawLine(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), x, 10, x, 100);
		//XFlush(disp);
		XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), x + 6, 59, "1", 1);
		XDrawString(disp, ventana, XDefaultGC(disp, DefaultScreen(disp)), x + 6, 70, "K", 1);
		XFlush(disp);
		x += 20;
		//sleep(1);
	}
	//printf("%d %d\n", i, x);

	dibujaRect(200, 200, 100, 50);
	sleep(5);
	XClearArea(disp, ventana, 200, 200, 100, 50, 1);
	XFlush(disp);

	sleep(100);
}