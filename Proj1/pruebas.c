#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cuentaDigitos(int n){
	int cta = 0;
	while(n){
		//printf("%d\n",n%10);
		n=n/10;
		cta++;
	}
	return cta;
}

char* numCadena(int n){
	int i = cuentaDigitos(n);
	char* numero = (char*)malloc(i);
	int j=i-1;
	while(n){
		numero[j--] = n%10 + '0';
		n = n / 10;
	}
	numero[i] = '\0';
	j=0;
	while(numero[j]!='\0'){
		printf("%c", numero[j++]);
	}puts(" ");
	
	return numero;
}


int main(){
	int n;
	scanf("%d",&n);
	printf("Digitos: %d\n",cuentaDigitos(n));
	//aux = numCadena(n);
	printf("En cadena: %s\n", numCadena(n));
	return 0;
}