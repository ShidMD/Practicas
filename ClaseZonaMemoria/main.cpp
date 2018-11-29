#define _CRT_SECURE_NO_WARNINGS
#include "ClaseZonaMemoria.h"
#include <string.h> // para strcpy
const unsigned int tamMem = 4096;
int16_t bytes[tamMem];

int main() {
	uint32_t * matrizEnteros;
	int nEnteros = 10;
	// Para manejar una matriz de enteros de 32 bits sin signo en la zona

	double * pReal;
	// Para manejar un real de 64 bits en la zona

	unsigned char * mensaje;
	int maxLongMensaje = 50;
	// Para manejar una cadena de caracteres de hasta 50 bytes

	ClaseZonaMemoria zona(tamMem, bytes);
	// Inicializa la zona para manejar hasta 4096 bytes = 4 KB

	if (!zona.reservaBloque((int16_t)(sizeof(uint32_t)) * nEnteros,(unsigned char **)&matrizEnteros)) return -1;
	// Reserva en la zona un bloque para manejar una matriz de enteros.
	// Guarda en 'matrizEnteros' su dirección

	if (!zona.reservaBloque(sizeof(double),(unsigned char **)&pReal)) return -1;
	// Reserva en la zona un bloque para manejar un real de tipo double.
	// Guarda su dirección en 'pReal'

	if (!zona.reservaBloque(maxLongMensaje,&mensaje)) return -1;
	// Reserva en la zona un bloque para manejar una cadena de 'maxLongMensaje' bytes.
	// Guarda su dirección en 'mensaje'

	for (int i = 0; i < nEnteros; i++)
		matrizEnteros[i] = i;
	*pReal = 33.33;
	strcpy((char*)mensaje, "aaaaa");
	// Guarda información en la matriz de enteros, en el real y en la cadena
	zona.liberaBloque((unsigned char**)&pReal); // ERROR EN LECTURA DE TAMAÑO
	// Libera de la zona el bloque ocupado por el real
	if (zona.zonaMemoriaFragmentada())
		zona.compactaZonaMemoria();
	// Si la zona está fragmentada, la compacta
	zona.borrar();
	return 0;
}