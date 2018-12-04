#include "ClaseZonaMemoria.h"

#include <stdio.h> // Para NULL
#include <string.h> // Para strcpy y memcpy

int8_t ClaseZonaMemoria::tamanoCabecera = sizeof(int16_t) + sizeof(void **);

ClaseZonaMemoria::ClaseZonaMemoria(int16_t t, int16_t * bytes) :

	tamano(t),
	fragmentada(false)
{
	this->pComienzo = (unsigned char*)bytes;
	this->pSiguienteReserva = this->pComienzo;
	memset(bytes,0,t);
}

int16_t ClaseZonaMemoria::sizeBlock(unsigned char * pBloque) {
	//devuelve el tamaño en valor absoluto de un puntero a un bloque
	return (*(int16_t*)pBloque < 0 ? *(int16_t*)pBloque * -1 : *(int16_t*)pBloque);
}

bool ClaseZonaMemoria::isFree(unsigned char * pBloque) {
	//devuelve si se puede escribir en el bloque apuntado
	return (*(int16_t *)pBloque <= 0);
}

bool ClaseZonaMemoria::reservaBloque(int16_t bSize, unsigned char ** pVar) {
	if (bSize + this->tamanoCabecera + this->pSiguienteReserva > this->pComienzo + this->tamano) return false;
	//Si el bloque no cabe en la memoria, return false.
	else {
		*this->pSiguienteReserva = bSize;
		//escribe el tamaño
		*(void **)(this->pSiguienteReserva + sizeof(int16_t)) = pVar;
		//guarda la dirección de la variable facilitada en memoria
		*pVar = this->pSiguienteReserva + this->tamanoCabecera;
		//Apunta el puntero de pVar a la dirección de la variable en memoria
		this->pSiguienteReserva += bSize + this->tamanoCabecera;
		//Desplaza pSiguienteReserva al final del bloque
		return true;
	}
}

void ClaseZonaMemoria::liberaBloque(unsigned char ** pValor) {
	if (!(this->isFree(*pValor - this->tamanoCabecera))) {
		//Si el bloque no está liberado ya, cambiar su valor a negativo
		*(int16_t*)(*pValor - this->tamanoCabecera) *= -1;
		*pValor = NULL;
		//Se pone el puntero a nulo
		this->fragmentada = true;
	}
}

void ClaseZonaMemoria::compactaZonaMemoria() { //-------------------OPTIMIZAR PROCEDIMIENTO----------------------//
	if (this->fragmentada) {
		unsigned char *reader, *writer;
		writer = this->pComienzo;
		reader = this->pComienzo;
		//declarar punteros de recorrido
		while (*(int16_t*)writer >0 ) {
			writer += this->tamanoCabecera + this->sizeBlock(writer);
		}
		//avanza el puntero buscando una zona libre para escribir
		reader = writer;
		while(reader!=0 && reader < this->pComienzo + this->tamano){
			while (*(int16_t*)reader < 0 && reader < this->pComienzo + this->tamano) {
			reader += this->tamanoCabecera + this->sizeBlock(reader);
			}
			if (*(int16_t*)reader == 0 || reader >= this->pComienzo + this->tamano)break;
			memcpy(writer, reader,(int16_t)(this->tamanoCabecera+ this->sizeBlock(reader)));
			writer += this->tamanoCabecera + this->sizeBlock(writer);
			reader += this->tamanoCabecera + this->sizeBlock(writer);

		}
		this->fragmentada = false;
	}
}
void ClaseZonaMemoria::borrar() {
	unsigned int i = 0;
	//variable de incremento
	while (this->pComienzo + i < this->pComienzo + this->tamano && *(int16_t*)(this->pComienzo + i)) {
		//mientras no se salga de memoria y el tamaño de bloque no sea 0
		*(unsigned char *)(*(unsigned char **)(this->pComienzo + i + sizeof(int16_t))) = NULL;
		//Poner la variable apuntada en memoria a NULL
		i += *(int16_t *)(this->pComienzo + i) + this->tamanoCabecera;
		//incrementar dirección hasta siguiente bloque
	}
	memset(this->pComienzo, 0, this->tamano);
	//Limpiar memoria con 0
	this->pSiguienteReserva = this->pComienzo;
	this->fragmentada = false;
	//Restaurar parámetros
}

bool ClaseZonaMemoria::zonaMemoriaFragmentada() {
	return this->fragmentada;
}