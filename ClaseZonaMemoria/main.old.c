#define _CRT_SECURE_NO_WARNINGS
#include "zonaMemoria.h"
#include <string.h> // para strcpy
//static uint32_t memMax = 4096;
unsigned char bytes[4096];
// Matriz de bytes donde se va a manejar la zona de memoria
int main() {
	ZonaMemoria zona;
	// Estructura para representar a la zona
	uint32_t *matrizEnteros;
	int nEnteros = 10;
	// Para manejar una matriz de enteros de 32 bits sin signo en la zona
	double *pReal;
	// Para manejar un real de 64 bits en la zona
	char *mensaje;
	int maxLongMensaje = 50;
	// Para manejar una cadena de caracteres de hasta 50 bytes
	inicializaZonaMemoria(bytes, 4096, &zona);
	// Inicializa la zona para manejar hasta 4096 bytes = 4 KB
	if (!reservaBloque(sizeof(uint32_t) * nEnteros, &matrizEnteros, &zona)) return -1;
	// Reserva en la zona un bloque para manejar una matriz de enteros.
	// Guarda en 'matrizEnteros' su dirección
	if (!reservaBloque(sizeof(double), &pReal, &zona)) return -1;
	// Reserva en la zona un bloque para manejar un real de tipo double.
	// Guarda su dirección en 'pReal'
	if (!reservaBloque(maxLongMensaje, &mensaje, &zona)) return -1;
	// Reserva en la zona un bloque para manejar una cadena de 'maxLongMensaje' bytes.
	// Guarda su dirección en 'mensaje'
	for (int i = 0; i < nEnteros; i++)
		matrizEnteros[i] = i;
	*pReal = 33.33;
	strcpy(mensaje, "aaaaa");
	// Guarda información en la matriz de enteros, en el real y en la cadena
	liberaBloque(pReal, &zona);
	// Libera de la zona el bloque ocupado por el real
	if (zonaMemoriaFragmentada(&zona))
		compactaZonaMemoria(&zona);
	// Si la zona está fragmentada, la compacta
	return 0;
}