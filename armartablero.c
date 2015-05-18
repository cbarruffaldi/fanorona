#include <stdio.h>
#include "fanorona.h"
#include "getnum.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ES_IMPAR(a) ((a) % 2 == 1)
#define ES_DIM_VALIDA(a, b) ( (a) >= MIN_DIM && (a) <= MAX_DIM && (b) >= MIN_DIM && (b) <= MAX_DIM )

int getlinea(char str[], int dim);

int guardarPartida(tTablero * tablero, int modo, const char * nombre);
tTablero cargarPartida(int * modo, const char * nombre);
tFlag leerSN(void);


void PedirDimensiones(tTablero * tablero){
	/*FUNCION DEL FRONT END*/
	tFlag hayError, decision;
	int cantfils, cantcols;

	do {
		hayError = 0;
		printf("Por favor, ingrese las dimensiones del tablero con el que desea jugar:\n");

		do {
			if (hayError)
				printf("No ingresó dimensiones correctas. Ingrese nuevamente:\n");
			cantfils= getint("Cantidad de Filas (impar entre %d y %d): ", MIN_DIM, MAX_DIM); 
			cantcols= getint("Cantidad de Columnas (impar entre %d y %d): ", MIN_DIM, MAX_DIM);
			putchar('\n');
			hayError = 1;
		} while ( !ES_IMPAR(cantfils) || !ES_IMPAR(cantcols) || !ES_DIM_VALIDA(cantfils, cantcols) || cantfils > cantcols);
		/* OJO si se ingresan mal las filas pide columnas igual. */

		printf("Las dimensiones del tablero serán: %d x %d\n\n", cantfils,cantcols);
		printf("¿Desea continuar?\nIngrese S si es así o N para ingresar nuevas dimensiones.\n");

		decision = leerSN();
	} while (decision == NO); /* se desean ingresar nuevas dimensiones */

	tablero->filas=cantfils;
	tablero->cols=cantcols;
	return;
}

/* LAS FUNCIONES QUE SIGUEN SON DEL BACK END */

void rellenarTablero(tTablero * tablero){
	int i,j;
	int postCentral=0;
	for(i=0; i<tablero->filas ; i++){
	for(j=0; j<tablero->cols; j++)
		{	
		if (i%2 == j%2)
			tablero->matriz[i][j].tipo= FUERTE;
		else
			 tablero->matriz[i][j].tipo= DEBIL;

		
		if (i < tablero->filas/2)
			tablero->matriz[i][j].ocupante = NEGRO;
		else if (i > tablero->filas/2)
			tablero->matriz[i][j].ocupante= BLANCO;
	
		else if (i == tablero->filas/2 && j != tablero->cols/2) /*Fila central (menos casilla central) */
		{	
			if (j%2==0)
				tablero->matriz[i][j].ocupante = postCentral ? BLANCO:NEGRO; /*No hay simetria con respecto a la central; se invierte la paridad luego de la misma*/
			else
				tablero->matriz[i][j].ocupante = postCentral ? NEGRO:BLANCO;
			
		}
		else{	/*Casilla central*/
			tablero->matriz[i][j].ocupante= VACIO;
			postCentral=1; /*Relevante para las otras piezas*/
		}	
	}	
	}
	
	return;
}

void liberarTablero(tTablero * tablero, int n){
	
	int i;
	for(i=0; i<n ; i++)
		free(tablero->matriz[i]);
	
	free(tablero->matriz);
			  
}

tTablero GenerarTablero(int fils, int cols)
{	int i;
	
	tTablero tablero;
	
	tablero.filas=fils;
	tablero.cols=cols;
	tablero.matriz=malloc(fils *sizeof(*tablero.matriz));

	if (tablero.matriz == NULL)
		return tablero;
		
	for(i=0; i< fils; i++)
	{	
		tablero.matriz[i]= malloc(cols*sizeof(tCasilla));
		
		if(tablero.matriz[i] ==NULL){
			liberarTablero(&tablero, i);
			return tablero;
		}
	}

	rellenarTablero(&tablero);
	
	return tablero;

}

/* FIN BACK END*/

/*LAS FUNCIONES QUE SIGUEN SON DE FRONT END*/
void ImprimirTablero ( tTablero * tablero )
{	int i, j;
	static char idColor[]={'B', 'N', 'O'}; /*BLANCO, NEGRO, VACIO*/

	for(i=0; i<tablero->filas; i++)
		{	putchar('\n');
			for(j=0; j<tablero->cols; j++)
				{	if (tablero->matriz[i][j].tipo==DEBIL)
						printf("%c   ", tolower( idColor[ tablero->matriz[i][j].ocupante ] )); /*BLANCO=0, NEGRO=1, VACIO=2*/
					else 
						printf("%c   ", idColor[ tablero->matriz[i][j].ocupante ]);
				}
		}
		putchar('\n');
	return;		
}	


/*main para probarlas */
int main (void)
{	int c;
	tTablero tablero;
	int i,j;
		
	PedirDimensiones(&tablero);
	
/*
	printf("Las dimensiones son : %d x %d \n", tablero.filas,tablero.cols);

	printf("Las dimensiones son : %d x %d \n", tablero.filas, tablero.cols);
*/
	
/*	tablero= GenerarTablero(tablero.filas,tablero.cols);*/

	tablero=cargarPartida(&i,"saved.bin"); 	
	if (tablero.matriz != NULL)
		ImprimirTablero(&tablero);
	
	return 0;
}
