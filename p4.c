#include <time.h>
#include <stdio.h>
#define max 1000000
int main(void){
	struct timespec tiempo1, tiempo2;
	int segaux;
	long nanoaux;
	int i = 0;
	int j = 6000;

	char arr[max];

	clock_gettime(CLOCK_REALTIME, &tiempo1);

	while(j--){
		while(i<max){
			arr[i++]='x';
		}
		i=0;
	}

	clock_gettime(CLOCK_REALTIME, &tiempo2);

	if(tiempo2.tv_nsec < tiempo1.tv_nsec){
		segaux=(int)tiempo2.tv_sec - (int)tiempo1.tv_sec - 1;
		nanoaux = tiempo1.tv_nsec - tiempo2.tv_nsec;
	}else{
		segaux=(int)tiempo2.tv_sec - (int)tiempo1.tv_sec;
		nanoaux = tiempo2.tv_nsec - tiempo1.tv_nsec;
	}
	printf("Segundos: %d\n", segaux);
	printf("Nanosegundos: %ld\n", nanoaux);
	
}