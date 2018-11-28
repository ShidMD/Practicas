#define _CRT_SECURE_NO_WARNINGS
#include "ClaseZonaMemoria.h"
#include <string.h> // para strcpy
const unsigned int memorySize = 4096;
unsigned char zonaReserva[memorySize];

int main() {
	ClaseZonaMemoria memoria(memorySize,zonaReserva);
	return 0;
}