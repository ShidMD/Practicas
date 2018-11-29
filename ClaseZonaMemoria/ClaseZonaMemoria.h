#ifndef CLASEZONAMEMORIA_H_
#define CLASEZONAMEMORIA_H_
#include <stdint.h>

class ClaseZonaMemoria {
private:
	unsigned int tamano;
	unsigned char * pComienzo;
	unsigned char * pSiguienteReserva;
	bool fragmentada;

	int16_t sizeBlock(unsigned char *);
	bool isFree(unsigned char *);

public:

	static int8_t tamanoCabecera;

	bool reservaBloque(int16_t, unsigned char **);
	void liberaBloque(unsigned char **);
	bool zonaMemoriaFragmentada();
	void compactaZonaMemoria();
	void borrar();
	ClaseZonaMemoria(int16_t, int16_t*);

};
#endif 