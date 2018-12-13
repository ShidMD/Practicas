#include "Arduino.h"
#include "Teclado4x4.h"
Teclado4x4::Teclado4x4(int F1, int F2, int F3, int F4, int C1, int C2, int C3, int C4,
	char * caracteres) {
	// Constructor al que le pasamos:
	// - F1, F2, F3, F4: salidas digitales de la placa Arduino conectadas a las se�ales
	// de las filas en el teclado
		// - C1, C2, C3, C4: entradas digitales de la placa Arduino conectadas a las
		// se�ales de las columnas en el teclado
		// - caracteres: La pulsaci�n de una tecla genera un car�cter. Aqu� se indican los
		// caracteres generados por la pulsaci�n de cada una de las 16 teclas, yendo por filas:
		// fila 1 columna 1, fila 1 columna 2, ..., fila 1 columna 4, fila 2 columna 1, ...,
		// fila 4 columna 4
	_salidasFilas[0] = F1;
	_salidasFilas[1] = F2;
	_salidasFilas[2] = F3;
	_salidasFilas[3] = F4;
	// Guarda los n�meros de se�al de las filas en _salidasFilas
	_entradasColumnas[0] = C1;
	_entradasColumnas[1] = C2;
	_entradasColumnas[2] = C3;
	_entradasColumnas[3] = C4;
	// Guarda los n�meros de se�al de las columnas en _entradasColumnas
	strcpy(_caracteres, caracteres);
	// Copia la cadena que define los caracteres de las teclas
}
void Teclado4x4::configura() {
	// M�todo a utilizar en setup() para inicializar las se�ales de manejo del teclado
	int i;
	for (i = 0; i < 4; i++) {
		pinMode(_entradasColumnas[i], INPUT_PULLUP);
		// Configura las entradas con resistencia pullup
		pinMode(_salidasFilas[i], INPUT);
		// Configura las salidas en principio como entradas
	}
	_pulsado = 0; // Indica que a�n no se puls� ninguna tecla
	_t = millis(); // Inicializa _t con el instante actual
}
int Teclado4x4::comprueba() {
	// M�todo a utilizar en loop() para comprobar si se ha detectado la pulsaci�n de una
	// nueva tecla. Devuelve:
	// - Un buleano falso si no se detect� una nueva pulsaci�n
	// - El car�cter correspondiente a una tecla si se detect� una nueva pulsaci�n
	int iSalida, iEntrada; // Contadores para recorrer entradas y salidas en bucles
	if (millis() - _t < 10)
		return 0;
	else _t = millis();
	// Para que haya como m�nimo un intervalo de 10 ms entre ejecuciones
	// de las siguientes instrucciones para evitar rebotes
	if (_pulsado) { // Si hab�a una tecla pulsada ...
		pinMode(_salidasFilas[_fila], OUTPUT);
		digitalWrite(_salidasFilas[_fila], LOW);
		// Activa la salida de la fila actual y la pone a nivel bajo
		_pulsado = digitalRead(_entradasColumnas[_columna]) == LOW;
		// La tecla sigue pulsada si la entrada en la columna actual est� a 0
		pinMode(_salidasFilas[_fila], INPUT);
		// Desactiva la salida de la fila
		if (!_pulsado) // Si se dej� de pulsar ...
			_t = millis(); // otros 10 ms para evitar rebotes
		return 0; // Indica que no es una nueva pulsaci�n
	}
	else { // Si no se estaba pulsando una tecla ...
		for (iSalida = 0; iSalida < 4 && !_pulsado; iSalida++) {
			// Recorre todas las salidas o hasta que se detecta una nueva pulsaci�n
			pinMode(_salidasFilas[iSalida], OUTPUT);
			digitalWrite(_salidasFilas[iSalida], LOW);
			// Activa la salida y la pone a nivel bajo
			for (iEntrada = 0; iEntrada < 4 && !_pulsado; iEntrada++) {
				// Recorre todas las entradas o hasta que se detecte una nueva pulsaci�n
				if (digitalRead(_entradasColumnas[iEntrada]) == LOW) {
					// Si la entrada est� a nivel bajo, hay una nueva pulsaci�n
					_pulsado = 1; // Indica que hay una nueva pulsaci�n
					_fila = iSalida;
					_columna = iEntrada;
					// Guarda la fila y columna de la tecla pulsada
				}
			}
			pinMode(_salidasFilas[iSalida], INPUT);
			// Desactiva la salida y la convierte en una entrada
		}
		if (_pulsado)
			return _caracteres[_fila * 4 + _columna];
		else return 0;
		// Si se detect� la pulsaci�n, devuelve el caracter correspondiente a la
		// tecla pulsada
	}
}
