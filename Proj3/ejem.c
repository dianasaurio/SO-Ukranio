#include <stdio.h>
#include <signal.h>
 
int foo = 1;
 
void catch(int sig)
{
    printf("Señal: %d atrapada!\n", sig);
    foo = 0;
}
 
int main(int argc, char *argv[])
{
    signal(SIGINT, &catch);
 
    while (foo)
    {
        // ... Esperar la señal de interrupción
    }
 
    return 0;
}