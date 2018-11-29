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

	if (!this->fragmentada) {
        unsigned char *reader = this->pComienzo;
        unsigned char *writer = reader;
        //Declarar punteros de recorrido

        while ( *(int16_t*)reader != 0 ) {
        //Mientras bSize no sea 0
        reader += tamanoCabecera + *reader;
        //Avanzar reader a siguiente bloque
            if (this->isFree(reader)) {
            //Comprobar si el bloque en lectura esta liberado
                *(int16_t*)writer=*(int16_t*)reader;
                //copiar bSize
                for (int i=0;i< this->sizeBlock(reader) + this->tamanoCabecera;i++) {
                    *(writer+i+tamanoCabecera)=*(reader+i+tamanoCabecera);
                }
                //escribir datos de lectura al cursor de escritura
                *(unsigned char **)(writer + sizeof(int16_t)) = writer + tamanoCabecera;
                //actualizar nueva posicion en el puntero de la variable
            }
            writer += this->tamanoCabecera + *(int16_t*)writer;
            //avanzar cursor writer
        };
        memset(writer,0,(this->pComienzo+this->tamano)-writer);
        //limpiar memoria restante
        this->pSiguienteReserva=writer;
        //actualizar dirección reserva
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