/* Tres en raya*/
#include <stdio.h>
#include <stdlib.h>

void crearTablero(char * matriz, int tam)
{
	int i;
	for (i=0;i<(tam*tam);i++) 
    {
		*(matriz + i)=' ';
    }
    return;
}
void printTablero(char *matriz, int tam)
{
    int i,j;
    for (i = -1; i < tam; i++) 
    {
		for (j = -1; j < tam; j++) 
		{
	    	printf("%c",matriz[i*tam+j]);
		}
			printf("\n");
    }
    return;
}
void agregarJugada(char *matriz, int tam, char ficha, int fila, int col)
{
	matriz[fila*tam + col] = ficha;
	return;
}

int  main()
{
	char *tablero;
	int tam_tablero;
	printf("Ingrese el tamano de la tabla \n");
    scanf("%d",&tam_tablero);
	tablero = (char *) malloc(tam_tablero * tam_tablero * sizeof(char));
	crearTablero(tablero,tam_tablero);
	agregarJugada(tablero,tam_tablero,'x',0,0);
	agregarJugada(tablero,tam_tablero,'x',1,0);
	printTablero(tablero,tam_tablero);
	free (tablero);
	return;

}