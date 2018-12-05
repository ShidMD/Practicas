#pragma once
// Para evitar incluir este archivo repetidamente
#include <stdint.h>
// Para uint16_t
typedef struct {
uint8_t tamano; // Tamaño de la zona de memoria en bytes
uint8_t * pComienzo; // Dirección de comienzo de la zona
uint8_t * pSiguienteReserva; // Dirección donde se va a hacer la siguiente reserva
uint8_t fragmentada;
 // Buleano cierto si la zona está fragmentada
} ZonaMemoria;
// Representa a una zona de memoria donde se va an a gestionar bloques de memoria reservados
// dinamicamente. En cada bloque se guarda previamente una cabecera con:
//
void inicializaZonaMemoria(void * p, uint16_t tamano, ZonaMemoria * pZona);
// Inicializa la zona de memoria que se va a manejar con la
// estructura apuntada por 'pZona' para manejar hasta 'tamano' bytes
// a partir de la dirección 'p'
int reservaBloque(int16_t nBytes, void ** p, ZonaMemoria * pZona);
// Reserva un bloque de memoria donde se va a guardar un
// memoria indicada en 'pZona'. En la dirección apuntada
// donde se encuentra el dato.
// Devuelve un buleano que es cierto si se pudo realizar


void liberaBloque(void * direccion, ZonaMemoria * pZona);
// Libera el bloque de memoria que corresponde al dato apuntado por 'direccion' en la zona de
// memoria indicada en 'pZona'
int zonaMemoriaFragmentada(ZonaMemoria * pZona);
// Devuelve un buleano cierto si la zona de memoria
// memoria indicada en 'pZona' está fragmentada
int sizeAbs(int16_t *a);
//Devuelve el valor absoluto del tamaño de los datos de bloque
void compactaZonaMemoria(ZonaMemoria * pZona);
// Compacta toda la zona de memoria eliminando huecos creados por
// la liberación de bloques
void borra(ZonaMemoria * pZona);
// Borra todos los bloques guardados en la zona de memoria indicada
// por 'pZona'
