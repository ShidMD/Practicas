#ifndef PANTALLAMIDAS_H_
#define PANTALLAMIDAS_H_
#include "Arduino.h"
class PantallaMidas {
	// Clase para el manejo de una pantalla LCD alfanum�rica de 4 filas y 40 columnas modelo
	// Midas MC44005A6W-FPTLW desde una placa Arduino. Se configura un bus de datos de 4 bits.
private: // Recursos privados de esta clase
	int _DB4, _DB5, _DB6, _DB7, _E1, _E2, _RS;
	// N�mero de se�ales Arduino utilizadas para la conexi�n a la pantalla
	int _fila;
	// �ltima fila posicionada 1...4
	void enviaOrden1(unsigned char orden);
	// Env�a una orden al controlador 1 de la pantalla
	void enviaOrden2(unsigned char orden);
	// Env�a una orden al controlador 2 de la pantalla
	void enviaOrden12(unsigned char orden);
	// Env�a una orden a los controladores 1 y 2 de la pantalla
	void busDatos4Bits(unsigned char dato);
	// Establece un valor para el bus de datos, utilizando los 4 bits
	// menos significativos del par�metro
	void pulsoE1();
	// Pulso a nivel alto en se�al E1 para transferencia con el controlador 1
	void pulsoE2();
	// Pulso a nivel alto en se�al E1 para transferencia con el controlador 1
public: // Miembros p�blicos de esta clase
	PantallaMidas(int DB4, int DB5, int DB6, int DB7, int E1, int E2, int RS);
	// Constructor al que se le indica qu� se�ales Arduino est�n conectadas a las
	// se�ales de la pantalla
	void configura();
	// M�todo que hay que utilizar en setup() para configurar e inicializar los
	// controladores de la pantalla
	void borra();
	// Borra toda la informaci�n mostrada en la pantalla
	void posiciona(int fila, int columna);
	// Posiciona el cursor en una fila (1...4) y columna (1...40)
	void escribeCadena(const char * cadena);
	// Escribe una cadena de caracteres en la posici�n actual del cursor
	void escribeCaracter(char caracter);
	// Escribe un car�cter en la posici�n actual del cursor
	void muestraCursor(int muestralo);
	// Hace que el cursor sea visible en funci�n del buleano que se pasa por par�metro
}; // Fin de la declaraci�n de la clase PantallaMidas
#endif
