#include "Arduino.h"
#include "PantallaMidas.h"
PantallaMidas::PantallaMidas(int DB4, int DB5, int DB6, int DB7, int E1, int E2, int RS) {
	// Constructor al que se le indica qu� se�ales Arduino est�n conectadas a las
	// se�ales de la pantalla
	_DB4 = DB4;
	_DB5 = DB5;
	_DB6 = DB6;
	_DB7 = DB7;
	_E1 = E1;
	_E2 = E2;
	_RS = RS;
	// Guarda los par�metros en datos privados
	_fila = 1; // La fila inicial es la primera
}
void PantallaMidas::configura() {
	// M�todo que hay que utilizar en setup() para configurar e inicializar los
	// controladores de la pantalla
	pinMode(_DB4, OUTPUT);
	pinMode(_DB5, OUTPUT);
	pinMode(_DB6, OUTPUT);
	pinMode(_DB7, OUTPUT);
	pinMode(_E1, OUTPUT);
	pinMode(_E2, OUTPUT);
	pinMode(_RS, OUTPUT);
	// Configura todas las se�ales como salidas digitales
	digitalWrite(_E1, LOW);
	digitalWrite(_E2, LOW);
	digitalWrite(_RS, LOW);
	// Pone a nivel bajo todas estas se�ales
	// A continuaci�n se ejecuta la secuencia de inicializaci�n de ambos controladores,
	// seg�n indicaciones recogidas de su manual
	delay(20); // Espera 20 ms para asegurar que la alimentaci�n se estabilice
	busDatos4Bits(3);
	pulsoE1();
	pulsoE2();
	// Transfiere a ambos controladores el valor 3
	delay(5); // Espera 5 ms
	busDatos4Bits(3);
	pulsoE1();
	pulsoE2();
	// Transfiere a ambos controladores el valor 3
	delay(1); // Espera 1 ms
	busDatos4Bits(3);
	pulsoE1();
	pulsoE2();
	// Transfiere a ambos controladores el valor 3
	delay(1); // Espera 1 ms
	busDatos4Bits(2);
	pulsoE1();
	pulsoE2();
	// Transfiere a ambos controladores el valor 2
	delay(1); // Espera 1 ms
		enviaOrden12(0x2D);
	delay(1); // Espera a que se ejecute la orden
	// Env�a la orden Function set con los bits:
	// DL=0 establece bus de 4 bits
	// N=1 establece manejo de 2 filas
	// F=1 establece juego de caracteres de 5x11 puntos
	enviaOrden12(0x08); // Display off
	delay(1); // Espera 1 ms para que se ejecute la orden
	borra(); // Clear display
	delay(2);

	enviaOrden12(0x06);
	delay(1);
	// Entry mode set:
	// ID=1 para que el cursor se mueva hacia derecha
	// SH=0 para que no haya desplazamiento de la pantalla
	enviaOrden12(0x0C); // Display on
	delay(1);
}
void PantallaMidas::busDatos4Bits(unsigned char dato) {
	// Establece un valor para el bus de datos, utilizando los 4 bits
	// menos significativos del par�metro
	if (dato & 0x01) // Si el bit 0 es un 1, entonces ...
		digitalWrite(_DB4, HIGH); // pon la se�al _DB4 a nivel alto
	else digitalWrite(_DB4, LOW); // si no, pon la se�al _DB4 a nivel bajo
	if (dato & 0x02) // Si el bit 1 es un 1, entonces ...
		digitalWrite(_DB5, HIGH); // pon la se�al _DB5 a nivel alto
	else digitalWrite(_DB5, LOW); // si no, pon la se�al _DB5 a nivel bajo
	if (dato & 0x04) // Si el bit 2 es un 1, entonces ...
		digitalWrite(_DB6, HIGH); // pon la se�al _DB6 a nivel alto
	else digitalWrite(_DB6, LOW); // si no, pon la se�al _DB6 a nivel bajo
	if (dato & 0x08) // Si el bit 3 es un 1, entonces ...
		digitalWrite(_DB7, HIGH); // pon la se�al _DB7 a nivel alto
	else digitalWrite(_DB7, LOW); // si no, pon la se�al _DB7 a nivel bajo
}
void PantallaMidas::pulsoE1() {
	// Pulso a nivel alto en se�al E1 para transferencia con el controlador 1
	digitalWrite(_E1, HIGH);
	digitalWrite(_E1, LOW);
}
void PantallaMidas::pulsoE2() {
	// Pulso a nivel alto en se�al E2 para transferencia con el controlador 2
	digitalWrite(_E2, HIGH);
	digitalWrite(_E2, LOW);
}
void PantallaMidas::enviaOrden1(unsigned char orden) {
	// Env�a una orden al controlador 1 de la pantalla
	digitalWrite(_RS, LOW); // Pone la se�al RS a nivel bajo
	busDatos4Bits(orden >> 4); // Pone los 4 bits m�s significativos en el bus de datos
	pulsoE1(); // Pulso en E1 para transferir esos bits
	busDatos4Bits(orden & 0x0F); // Pone los 4 bits menos significativos en el bus de datos
	pulsoE1(); // Pulso en E1 para transferir esos bits
}
void PantallaMidas::enviaOrden2(unsigned char orden) {
	// Env�a una orden al controlador 2 de la pantalla
	digitalWrite(_RS, LOW); // Pone la se�al RS a nivel bajo
	busDatos4Bits(orden >> 4); // Pone los 4 bits m�s significativos en el bus de datos
	pulsoE2(); // Pulso en E2 para transferir esos bits
	busDatos4Bits(orden & 0x0F); // Pone los 4 bits menos significativos en el bus de datos
	pulsoE2(); // Pulso en E2 para transferir esos bits
}
void PantallaMidas::enviaOrden12(unsigned char orden) {
	// Env�a una orden a ambos controladores
	enviaOrden1(orden); // Env�a la orden al controlador 1
	enviaOrden2(orden); // Env�a la orden al controlador 2
}
void PantallaMidas::muestraCursor(int muestralo) {
	// Hace que el cursor sea visible en funci�n del buleano que se pasa por par�metro
	unsigned char orden1, orden2;
	if (muestralo) { // Si hay que mostrarlo ...
		if (_fila < 3) { // Si es para el controlador 1 ...
			orden1 = 0x0F; // Muestra cursor en 1
			orden2 = 0x0C; // Oculta cursor en 2
		}
		else {
			orden1 = 0x0C; // Oculta cursor en 1
			orden2 = 0x0F; // Muestra cursor en 2
		}
	}
	else { // Si hay que ocultarlo ...
		orden1 = 0x0C; // Oculta cursor en 1
		orden2 = 0x0C; // Oculta cursor en 2
	}
	enviaOrden1(orden1); // Env�a la orden al controlador 1
	enviaOrden2(orden2); // Env�a la orden al controlador 2
}
void PantallaMidas::borra() {
	// Borra toda la informaci�n mostrada en la pantalla
	enviaOrden12(0x01);
	// Env�a la orden de c�digo 0x01 a los dos controladores
	delay(2); // Espera 2 ms a que se termine de ejecutar
}
void PantallaMidas::escribeCaracter(char caracter) {
	// Env�a un car�cter a la pantalla, que se mostrar� en la posici�n actual del cursor.
	// La posici�n del cursor se incrementa
	digitalWrite(_RS, HIGH); // Pone la se�al RS a nivel alto
	busDatos4Bits(caracter >> 4); // Pone los 4 bits m�s significativos en el bus de datos
	if (_fila < 3) // Si es para el controlador 1 ...
		pulsoE1(); // pulso en E1 para transferir esos bits al controlador 1
	else pulsoE2(); // si no, pulso en E2 para transferir esos bits al controlador 2
	busDatos4Bits(caracter & 0x0F); // Pone los 4 bits menos significativos en el bus de datos
	if (_fila < 3) // Si es para el controlador 1 ...
		pulsoE1(); // pulso en E1 para transferir esos bits al controlador 1
	else pulsoE2(); // si no, pulso en E2 para transferir esos bits al controlador 2
	delay(1); // Retardo de 1 ms para esperar a que se escriba el car�cter
}

void PantallaMidas::escribeCadena(const char * cadena) {
	// Escribe una cadena de caracteres en la posici�n actual del cursor
	int i; // Contador para el bucle
	i = 0; // Desde el comienzo de la cadena ...
	while (cadena[i]) // Mientras no se llegue a un byte con valor 0 ...
		escribeCaracter(cadena[i++]); // Escribe el car�cter y pasa al siguiente
}
void PantallaMidas::posiciona(int fila, int columna) {
	// Posiciona el cursor en una fila (1...4) y columna (1...40)
	int posicion; // Posici�n en la memoria interna del controlador
	if (fila < 3) { // Si es para el primer controlador ...
		posicion = (fila - 1) * 0x40 + columna - 1;
		// La primera posici�n comienza en 0 para la fila 1 y en 0x40 para la fila 2
		// Al avanzar en las columnas, se avanza en memoria a posiciones consecutivas
		enviaOrden1(0x80 | posicion);
		// Env�a una orden al controlador 1 con la nueva posici�n del cursor
	}
	else { // Lo mismo para el controlador 2
		posicion = (fila - 3) * 0x40 + columna - 1;
		enviaOrden2(0x80 | posicion);
	}
	delay(1); // Espera 1 ms a que el cursor se posicione
	_fila = fila; // Recuerda la fila donde est� situado el cursor
}