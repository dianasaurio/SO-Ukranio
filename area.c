#include <stdio.h>
#include <sys/types.h>
#include <math.h>

int main(int argc, char *argv[]){

	double i;
	int n = atoi(argv[1]);
	float delta = 1.0 / n;
	double area = 0.0;
	double y = 0.0;
	double temp;

	for(i=delta;i<=1.0;i=i+delta){
		y = sqrtl(1-(i)*(i));
		temp = delta*y;
		//printf("i: %lf, y: %lf, rectangulo: %lf\n", i, y, temp);
		area += temp;
	}
	printf("%.16lff\n", area*4);
	printf("pi = %.16lff\n", acos(-1));



	return 0;
}