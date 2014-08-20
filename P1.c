#include <stdio.h>
#include <string.h>
int main()
{
	char caracter = 0;
	int entero = 0;
	float flotante = 0;
	long largo = 0;
	double doble = 0;

	printf("CARACTER....Direccion: %p Tam: %d \n", &caracter, sizeof(char));
	printf("ENTERO....Direccion: %p Tam: %d \n", &entero, sizeof(int));
	printf("FLOTANTE....Direccion: %p Tam: %d \n", &flotante, sizeof(float));
	printf("LARGO....Direccion: %p Tam: %d \n", &largo, sizeof(long));
	printf("DOBLE....Direccion: %p Tam: %d \n", &doble, sizeof(double));

	puts("--------------------------------------------------------");

	char *pcaracter;
	int *pentero;
	float *pflotante;
	long *plargo;
	double *pdoble;

	printf("APUNTADOR A CARACTER....Direccion: %p Tam: %d\n", &pcaracter, sizeof(pcaracter));
	printf("APUNTADOR A ENTERO....Direccion: %p Tam: %d\n", &pentero, sizeof(pentero));
	printf("APUNTADOR A FLOTANTE....Direccion: %p Tam: %d\n", &pflotante, sizeof(flotante));
	printf("APUNTADOR A LARGO....Direccion: %p Tam: %d\n", &plargo, sizeof(plargo));
	printf("APUNTADOR A DOBLE....Direccion: %p Tam: %d\n", &pdoble, sizeof(pdoble));

	puts("--------------------------------------------------------");

	char cadena[] = "ESCOM - IPN";
	int i;
	for(i = 0 ; i < strlen(cadena) ; i++){
		printf("%p\n", &cadena[i]);
	}

	printf("ASCII de fin de cadena en la posición +%d: CARACTER = %c, ASCII = %d\n", i, cadena[i], cadena[i]);

	return 0;
}