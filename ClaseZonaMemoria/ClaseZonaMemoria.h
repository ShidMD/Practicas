#ifndef CLASEZONAMEMORIA_H_
#define CLASEZONAMEMORIA_H_
#include <stdint.h>

class ClaseZonaMemoria {
private:
	unsigned int tamano;
	int16_t * pComienzo;
	int16_t * pSiguienteReserva;
	bool fragmentada;

	int16_t sizeBlock(int16_t *);
	bool isFree(int16_t *);

public:

	static int8_t tamanoCabecera;

	bool reservaBloque(int16_t, void **);
	void liberaBloque(int16_t *);
	bool zonaMemoriaFragmentada();
	void compactaZonaMemoria();
	void borrar();
	ClaseZonaMemoria(int16_t, unsigned char *);

};
#endif 