#include "PantallaMidas.h"
#include "Teclado4x4.h"
Teclado4x4 teclado(22, 23, 24, 25, 26, 27, 28, 29, "789s456b123d.0ei");
// Construye un objeto para manejar el teclado utilizando las l�neas digitales 22 a 29.
// Es un teclado de 4x4 teclas. A cada tecla le corresponde un car�cter indicado en el �ltimo
// par�metro, recorriendo las teclas por filas de izquierda a derecha y de arriba a abajo.
PantallaMidas pantalla(32, 33, 34, 35, 36, 37, 38);
// Construye un objeto para manejar la pantalla utilizando las l�neas digitales 32 a 38.

void setup() {
	teclado.configura(); // Configura las se�ales Arduino para el teclado
	pantalla.configura();
	// Configura las se�ales Arduino y env�a la secuencia de �rdenes de inicializaci�n
	// a la pantalla
	pantalla.posiciona(1, 1); // Sit�a el cursor en la fila 1, columna 1
	pantalla.escribeCadena("Prueba de teclado y pantallla");
	// Escribe una cadena de caracteres a partir de esa posici�n
	pantalla.posiciona(3, 1); // Sit�a el cursor en la fila 3, columna 1
	pantalla.muestraCursor(1); // Hace que el cursor se haga visible
}
void loop() {
	char caracter;
	caracter = teclado.comprueba(); // Comprueba el teclado
	if (caracter) // Si se puls� el teclado ...
		pantalla.escribeCaracter(caracter); // visualiza el car�cter
}