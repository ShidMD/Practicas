#include "ClaseZonaMemoria.h"

#include <stdio.h> // Para NULL
#include <string.h> // Para strcpy y memcpy

int8_t ClaseZonaMemoria::tamanoCabecera = sizeof(int16_t) + sizeof(void **);

ClaseZonaMemoria::ClaseZonaMemoria(int16_t t, unsigned char * bytes) :

	tamano(t),
	pComienzo(bytes),
	pSiguienteReserva(bytes),
	fragmentada(false)
{
	memset(bytes,0,t);
}

int16_t ClaseZonaMemoria::sizeBlock(int16_t * pBloque) {
	//devuelve el tamaño en valor absoluto de un puntero a un bloque
	return (*pBloque < 0 ? *pBloque * -1 : *pBloque);
}

bool ClaseZonaMemoria::isFreeBlock(int16_t * pBloque) {
	//devuelve si se puede escribir en el bloque apuntado
	return (*(int16_t *)pBloque > 0);
}

bool ClaseZonaMemoria::reservaBloque(int16_t bSize, void ** pVar) {
	if (bSize + this->tamanoCabecera + this->pSiguienteReserva > this->pComienzo + this->tamano) return false;
	else {
		*(int16_t *)this->pSiguienteReserva = bSize;
		*(void **)(this->pSiguienteReserva + sizeof(int16_t)) = pVar;
		*pVar = this->pSiguienteReserva + this->tamanoCabecera;
		this->pSiguienteReserva += bSize + this->tamanoCabecera;
		return 1;
	}
}

void ClaseZonaMemoria::liberaBloque(int16_t * pValor) {
	if (!this->isFreeBlock(pValor - this->tamanoCabecera)) {
		*(pValor - this->tamanoCabecera) *= -1;
		pValor = NULL;
	}
	this->fragmentada = true;
}

void ClaseZonaMemoria::compactaZonaMemoria() {


}
void ClaseZonaMemoria::borrar() {
	unsigned int i = 0;
	while (this->pComienzo + i < this->pComienzo + this->tamano && *(int16_t*)(this->pComienzo + i)) {
		*(unsigned *)(*(unsigned **)(this->pComienzo + i + sizeof(int16_t))) = NULL;
		i += *(int16_t *)(this->pComienzo + i) + this->tamanoCabecera;
	}
	memset(this->pComienzo, 0, this->tamano);
}

bool ClaseZonaMemoria::zonaMemoriaFragmentada() {
	return this->fragmentada;
}