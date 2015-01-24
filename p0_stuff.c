#include <stdio.h>

int cuentaDigitos(int n){
	int cta = 0;
	while(n){
		printf("%d\n",n%10);
		n=n/10;
		cta++;
	}
	return cta;
}

int main(){
	int n;
	scanf("%d",&n);
	printf("Digitos: %d\n",cuentaDigitos(n));
	return 0;
}