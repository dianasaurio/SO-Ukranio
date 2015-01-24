#include<errno.h>
#include<dirent.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>

char buffer[1]; 
char buffer3[100];
int main(int argc, char *argv[])
{
DIR *dip;
struct dirent *dit;
char mensaje[100];
int i=0, j=0, k=0 ,m=0,h=0,h1=0,h2=0,h3=0,h4=0,h5=0,h6=0,h7=0,h8=0;
char prueba[]="processor";
int nbytes, origen, proceso;
dip = opendir(argv[1]);
pid_t pid;


proceso=open("/proc/cpuinfo", O_RDONLY);
		while((nbytes = read(proceso, buffer3, sizeof buffer3)) > 0){
			if(strstr(buffer3, prueba)){ 
			j++;
			}
		}
close(proceso);
		while ((dit = readdir(dip)) != NULL){
			m++;
		}

h=m/j; //Numero de archivos para cada proceso.
h1=h;
h2=h;
h3=h;
h4=h;
h5=h;
h6=h;
h7=h;
h8=h;
int a=h;

while(m!=a){
			if(m%2==1){ h=h+1; a=a+1;}
			if(m!=a){ 
			a=a+h;
			h1=h+h1;
			}
			if(m!=a){ 
			a=a+h;
			h2=h1+h2;
			}
			if(m!=a){ 
			a=a+h;
			h3=h2+h3;
			}
			if(m!=a){ 
			a=a+h;
			h4=h3+h4;
			}
			if(m!=a){ 
			a=a+h;
			h5=h4+h5;
			}
			if(m!=a){ 
			a=a+h;
			h6=h5+h6;
			}
			if(m!=a){ 
			a=a+h;
			h7=h6+h7;
			}
			if(m!=a){ 
			a=a+h;
			h8=h7+h8;
			}
}

closedir(dip);
dip = opendir(argv[1]);
printf("Se encontraron %d nucleos.\n", j);
fflush(stdin);
printf("ARCHIVO\t\t\t\tPID\t\tNO.CARACTERES '%s' ENCONTRADOS\n", argv[2]);
	while ((dit = readdir(dip)) != NULL)
		{
					if(k==h8){
					pid=fork();		
					wait(1);
					if(pid!=0){ exit(0);}}
				
					if(k==h7){
					pid=fork();		
					wait(1);
					if(pid!=0){ exit(0);}}

					if(k==h6){
					pid=fork();		
					wait(1);
					if(pid!=0){ exit(0);}}

					if(k==h5){
					pid=fork();		
					wait(1);
					if(pid!=0){ exit(0);}}

					if(k==h4){
					pid=fork();		
					wait(1);
					if(pid!=0){ exit(0);}}

					if(k==h3){
					pid=fork();		
					wait(1);
					if(pid!=0){ exit(0);}}

					if(k==h2){
					pid=fork();		
					wait(1);
					if(pid!=0){ exit(0);}}

					if(k==h1){
					pid=fork();		
					wait(1);
					if(pid!=0){ exit(0);}}

					if(k==h){
					pid=fork();		
					wait(1);

					if(pid!=0){ exit(0);}}
					i=0;
					k++;


					if (dit -> d_type != 8){ printf(""); } else{
					printf("%s", dit->d_name);
					printf("\t\t\t%d\t",getpid());
					sprintf(mensaje, "%s/%s", argv[1], dit->d_name);
					origen = open(mensaje, O_RDONLY);
						while((nbytes = read(origen, buffer, sizeof buffer)) > 0){
							if(strstr(buffer, argv[2])){ 
							i++;
						}
					}	
					printf("\t\t%d\n", i);
					close(origen);
					fflush(stdin);	
				}
		}
	closedir(dip);
	exit(0);
} 

