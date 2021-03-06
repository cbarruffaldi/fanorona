#ifndef __fanorona_header

#define __fanorona_header

/* 
** empieza en -120 porque así comparamos si es menor a 0, ya es error.
** imprimirError() imprime el error correspondiente. Ir actualizando-
**/ 
enum tOpcion {PVE=0, PVP, CARGAR, SALIR};
enum tError {ERR_FMT= -120, ERR_FMT_SAVE1, ERR_FMT_SAVE2, ERR_FMT_MOV1, ERR_FMT_MOV2, ERR_MOV_ORIG, ERR_MOV_DEST, ERR_MOV_TOC, ERR_MOV_DIR, ERR_MOV_PAIKA, ERR_MOV_RANGO, ERR_MOV_NO_ADY,ERR_MOV_DEBIL, ERR_MOV_AMBIGUO, ERR_UNDO, ERR_UNDO_DOBLE, ERR_MEM_COMPU};
enum tEstado {LIBRE=0, TOCADA, ACTIVA};
enum tJugada {START=-1, QUIT, SAVE, UNDO, MOV};
enum tCaptura {NINGUNO=0, WITHDRAWAL, APPROACH, AMBOS}; 
enum tDireccion {N=1, S, E, O, NE, NO, SE, SO, NULA};

typedef struct {
	char tipo; /* debil o fuerte */
	unsigned char ocupante; /* blanco, negro o vacio*/
	int estado;
} tCasilla;

typedef struct {
	int fil;
	int col;
} tCoordenada;

typedef struct {
	tCoordenada coordOrig;
	tCoordenada coordDest;
	char tipoMov; /* approach, withdrawal o ninguno */
} tMovimiento;

typedef struct{
	tCasilla ** matriz;
	tCasilla ** tableroAuxiliar;
	int filas;
	int cols;
}tTablero;

typedef signed char tFlag;

#define ERROR -1

#define BLANCO 0
#define NEGRO  1
#define VACIO  2

#define FUERTE 1 
#define DEBIL 2

#define MIN_DIM 3 /* minima dimensión de tablero permitida */
#define MAX_DIM 19 /* máxima dimensión de tablero permitida */


#define BORRA_BUFFER while (getchar() != '\n')
#define STR_DIM 41 /* long del vector que se usará para guardar la entrada del usuario */
#define LONG_SAVE 5 /* longitud del str "save " */
#define MIN_STR 4
#define MIN_MOV 12 /* no está en uso. borrar o revisar */
#define MAX_MOV 19 /* no está en uso. borrar o revisar */
#define MAX_NOM (STR_DIM - LONG_SAVE - 5) /* Maxima logitud para <filename>: se resta la lonngitud de "save " y -5 por el '\0' y para
					  ** saber si el usuario escribió más que el límite permitido */
#define OK 1
int getlinea(char str[], int dim);

#endif
