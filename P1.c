#include <stdio.h>

int main()
{
	char caracter = 0;
	int entero = 0;
	float flotante = 0;
	double doble = 0;

	printf("CARACTER....Direccion: %p Tam: %d \n", &caracter, sizeof(char));
	printf("ENTERO....Direccion: %p Tam: %d \n", &entero, sizeof(int));
	printf("FLOTANTE....Direccion: %p Tam: %d \n", &flotante, sizeof(float));
	printf("DOBLE....Direccion: %p Tam: %d \n", &doble, sizeof(double));
	puts("--------------------------------------------------------");

	double* apuntador;
	apuntador = &doble;
	printf("Una direccion de memoria ocupa: %d\n", sizeof(apuntador));

	return 0;
}