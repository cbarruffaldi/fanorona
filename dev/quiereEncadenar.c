/* FRON-END 
** entrada: puntero del tMovimiento movimiento anterior.
** salida: booleano. 0 si no se desea encadenar o 1 en caso contrario.
**	   Pide al usuario nueva dirección de destino y actualiza al tMovimiento de forma acorde.
*/

#include "fanorona.h"
#include <stdio.h>
#include <string.h>

#define STR_DIM2 30
#define MIN_STR2 5 /* mínima longitud de string de coordenada válida que puede escribir el usuario */
#define MAX_STR2 10  /* máxima longitud de string de coordenada válida que puede escribir el usuario */

int getlinea(char str[], int dim);
tFlag validarMovFormato (const char str[], tMovimiento *mov);
void imprimirError(tFlag error);

void pedirCadena (tMovimiento *mov) {
	tFlag esValido = 1;
	char str[STR_DIM2]; 
	char nuevoStr[15]; /* tamaño suficiente para evaluar si el usuario introdujo de más */
	int fo, co;
	int n;

	fo = ++(mov->coordOrig.fil); /* sumamos 1 a las coordenadas, pues leerCoord les resta 1 */
	co = ++(mov->coordOrig.col);

	printf("Puede encadenar una movimiento!\n");
	printf("Ingrese solo la coordenada de la casilla a la que desea moverse y el tipo de captura si es necesario\n");
	printf("Se imprimira su nueva casilla de origen.\n");

	do {
		imprimirError(esValido); /* en una primer instancia no imprimirá nada, pues esValido es mayor a 0 */

		printf("> M [%d,%d]", fo, co);

		n = getlinea(nuevoStr, 15);

		if (n >= MIN_STR2 && n <= MAX_STR2) {
			sprintf(str, "M [%d,%d]%s", fo, co, nuevoStr);
			esValido = validarMovFormato (str, mov); /* devuelve menor a 0 en caso de error */
		}
		else
			esValido = ERR_FMT_MOV1;

	} while (esValido < 0); /* si es menor a cero es error */

	return; 
}

/* TESTEO
int main(void) {
	tMovimiento mov;
	mov.coordOrig.fil = 4;
	mov.coordOrig.col = 7;
	mov.coordDest.fil = 9;
	mov.coordDest.col = 10;

	printf("Coordenada anterior:\n");
	printf("[%d,%d] [%d,%d]\n", mov.coordOrig.fil, mov.coordOrig.col, mov.coordDest.fil, mov.coordDest.col);

	if (quiereEncadenar(&mov)) {
		printf("Nueva coordenada:\n");
		printf("[%d,%d] [%d,%d]\n", mov.coordOrig.fil, mov.coordOrig.col, mov.coordDest.fil, mov.coordDest.col);
	}
	else
		printf("No quiere encadenar\n");

	return 0;
}*/
