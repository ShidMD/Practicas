#ifndef CLASEZONAMEMORIA_H_
#define CLASEZONAMEMORIA_H_
#include <stdint.h>

class ClaseZonaMemoria {
private:
	unsigned int tamano;
	unsigned char * pComienzo;
	unsigned char * pSiguienteReserva;
	bool fragmentada;

	int16_t sizeBlock(int16_t *);
	bool isFreeBlock(int16_t *);

public:

	static int8_t tamanoCabecera;

	bool reservaBloque(int16_t, void **);
	void liberaBloque(int16_t *);
	bool esFragmentada();
	void compactar();
	void borrar();
	ClaseZonaMemoria(int16_t, unsigned char *);

};
#endif 