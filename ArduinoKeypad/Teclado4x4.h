#ifndef TECLADO4X4_H_
#define TECLADO4X4_H_
#include "Arduino.h"
class Teclado4x4 {
private:
	int _salidasFilas[4]; // Salidas digitales de la placa Arduino conectadas a las filas
	int _entradasColumnas[4]; // Entradas digitales de la placa Arduino conectadas a columnas
	char _caracteres[17]; // Los 16 caracteres que corresponden a cada tecla
	int _pulsado; // Buleano cierto si se puls� alguna tecla
	int _fila, _columna; // Fila y columna donde se detect� la pulsaci�n
	unsigned long _t; // Tiempo para control de rebotes en los pulsadores
public:
	Teclado4x4(int F1, int F2, int F3, int F4, int C1, int C2, int C3, int C4,
		char * caracteres);
	// Constructor al que le pasamos:
	// - F1, F2, F3, F4: salidas digitales de la placa Arduino conectadas a las se�ales
	// de las filas en el teclado
	// - C1, C2, C3, C4: entradas digitales de la placa Arduino conectadas a las
	// se�ales de las columnas en el teclado
	// - caracteres: La pulsaci�n de una tecla genera un car�cter. Aqu� se indican los
	// caracteres generados por la pulsaci�n de cada una de las 16 teclas, yendo por filas:
	// fila 1 columna 1, fila 1 columna 2, ..., fila 1 columna 4, fila 2 columna 1, ...,
	// fila 4 columna 4
	void configura();
	// M�todo a utilizar en setup() para inicializar las se�ales de manejo del teclado
	int comprueba();
	// M�todo a utilizar en loop() para comprobar si se ha detectado la pulsaci�n de una
	// nueva tecla. Devuelve:
	// - Un buleano falso si no se detect� una nueva pulsaci�n
	// - El car�cter correspondiente a una tecla si se detect� una nueva pulsaci�n
};
#endif
