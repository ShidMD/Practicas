#include "zonaMemoria.h"
#include <stdio.h> // Para NULL
#include <string.h> // Para strcpy y memcpy
static int tamanoCabecera = sizeof(int16_t) + sizeof(void**);
// Tamaño de la cabecera de cada bloque de memoria
/* Define el tamaño de la cabecera útilizando la función sizeof() y pasando los objetos a almacenar*/
void inicializaZonaMemoria(void * p, uint16_t tamano, ZonaMemoria * pZona) {
    // Inicializa la zona de memoria que se va a utilizar con la
    // estructura apuntada por 'pZona' para manejar hasta 'tamano' bytes
    // a partir de la dirección 'p'
    pZona->pComienzo = p; // Guarda la dirección de comienzo de la zona de memoria dinámica
    pZona->tamano = tamano; // Guarda el tamaño de bytes de la zona de memoria
    pZona->pSiguienteReserva = p; // Donde debe situarse un bloque nuevo
    pZona->fragmentada = 0; // Si la zona de memoria dinámica es compactable
    memset(p, 0, tamano); // Pone a 0 toda la zona de memoria. Necesario para identificar una cabecera vacía.
}

int reservaBloque(int16_t nBytes, void ** pp, ZonaMemoria * pZona) {
// Reserva un bloque de memoria donde se va a guardar un dato de tamaño 'nBytes' bytes en la zona de
// memoria indicada en el puntero 'pZona'. En la dirección apuntada por 'pp' guarda la dirección de memoria
// donde se encuentra el dato.
// Devuelve un buleano que es cierto si se pudo realizar la reserva.
    if (pZona->pSiguienteReserva + tamanoCabecera + nBytes > pZona->pComienzo + pZona->tamano) return 0;
    // Calcula el tamo de bloque y ,si se saldría de la zona de memoria, devuelve falso
    else {
        // Si cabe ...
        *(int16_t *)(pZona->pSiguienteReserva) = nBytes;
        // En esa dirección se guarda el número de bytes como un entero de 2 bytes
        *(int16_t **)(pZona->pSiguienteReserva + sizeof(int16_t)) = pp;
        // A continuación se guarda la dirección del puntero de datos
        *pp = pZona->pSiguienteReserva + tamanoCabecera;
        // Se devuelve en el puntero de datos la dirección de los datos
        pZona->pSiguienteReserva += tamanoCabecera + nBytes;
        // Se actualiza la posición para la siguiente reserva
        memset(*pp, 0, nBytes);
        // Pone todos los bytes del dato a 0
        return 1;
        }
    }
// Indica que se pudo reservar el bloque

void liberaBloque(int8_t* direccion, ZonaMemoria * pZona) {
    // Libera el bloque de memoria apuntado por 'direccion' en la zona de
    // memoria indicada en 'pZona'
    *(int16_t *)(direccion-tamanoCabecera) *=-1;
    //Invierte el signo del tamaño del bloque para cosiderarlo liberado
	direccion = NULL;
    //Coloca el puntero de la variable en NULL
    pZona->fragmentada=1;
    //Determina que la zona de memoria esta fragmentada

}
int zonaMemoriaFragmentada(ZonaMemoria * pZona) {
    // Devuelve un buleano cierto si la zona de memoria
    // indicada en 'pZona' está fragmentada
    return pZona->fragmentada;
}

int sizeAbs (int16_t* a) {
	//Obtiene el valor absoluto de nBytes
	if (*a < 0) return *a *= -1;
	return *a;
}

void compactaZonaMemoria(ZonaMemoria * pZona) {
    // Compacta toda la zona de memoria, eliminando huecos creados por
    // la liberación de bloques


    if (pZona->fragmentada) {
        uint8_t *writer = pZona->pComienzo;
		uint8_t *reader;
        //Declarar punteros de recorrido (como punteros a int16_t para simplificar las llamadas a bSize)

		while ((*(int16_t)writer > 0)&&(writer < pZona->pComienzo + pZona->tamano)) writer += tamanoCabecera + sizeAbs(writer);
		//Busca el primer bloque disponible para empezar a copiar
		reader = writer;
		//Coloca el puntero de lectura

        while ( (*(int16_t*)reader != 0)||(reader < pZona->pComienzo+pZona->tamano)) {
        //Copia bloques hasta que el puntero de lectura llegue al final o a un bloque tamaño 0

			while (*(int16_t*)reader < 0) reader += tamanoCabecera + sizeAbs(reader); 
			//Avanzar reader a siguiente bloque que no sea libre
				if (*(int16_t*)reader > 0){
				//Si es un bloque ocupado, copiar a writer, si fuera 0, sigue
					memcpy(writer,reader,tamanoCabecera + sizeAbs(reader));
				//Copiar bloque
                }
         writer += tamanoCabecera + sizeAbs(writer);
            //avanzar cursor writer al siguiente espacio
		 reader += tamanoCabecera + sizeAbs(writer);
			//avanza cursor reader al siguiente bloque (lee el tamaño del bloque actual de writer por que el de reader puede haber sido machacado)
        };
        memset(writer,0,(pZona->pComienzo+pZona->tamano)-writer);
        //limpiar memoria restante
        pZona->pSiguienteReserva=writer;
        //actualizar dirección reserva
		pZona->fragmentada = 0;
    }

}
void borra(ZonaMemoria * pZona) {
    // Borra todos los datos guardados en la zona de memoria indicada
    // por 'pZona'
	uint8_t *reader;
	reader = pZona->pComienzo;
	while ((*(int16_t*)reader != 0) || (reader < pZona->pComienzo + pZona->tamano )) {
		//Poner punteros de las variables enlazadas a NULL
		(int16_t *)(*(int16_t **)(reader + sizeof(int16_t))) = NULL;
		reader += sizeAbs(reader) + tamanoCabecera;
	}

    memset(pZona->pComienzo, 0, pZona->tamano);
	//Poner a cero toda la memoria
    pZona->fragmentada=0;
    pZona->pSiguienteReserva=pZona->pComienzo;
	//Resetear propiedades de zonaMemoria convenientes
}
