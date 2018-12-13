#include "PantallaMidas.h"
#include "Teclado4x4.h"
Teclado4x4 teclado(22, 23, 24, 25, 26, 27, 28, 29, "789s456b123d.0ei");
// Construye un objeto para manejar el teclado utilizando las líneas digitales 22 a 29.
// Es un teclado de 4x4 teclas. A cada tecla le corresponde un carácter indicado en el último
// parámetro, recorriendo las teclas por filas de izquierda a derecha y de arriba a abajo.
PantallaMidas pantalla(32, 33, 34, 35, 36, 37, 38);
// Construye un objeto para manejar la pantalla utilizando las líneas digitales 32 a 38.

void setup() {
	teclado.configura(); // Configura las señales Arduino para el teclado
	pantalla.configura();
	// Configura las señales Arduino y envía la secuencia de órdenes de inicialización
	// a la pantalla
	pantalla.posiciona(1, 1); // Sitúa el cursor en la fila 1, columna 1
	pantalla.escribeCadena("Prueba de teclado y pantallla");
	// Escribe una cadena de caracteres a partir de esa posición
	pantalla.posiciona(3, 1); // Sitúa el cursor en la fila 3, columna 1
	pantalla.muestraCursor(1); // Hace que el cursor se haga visible
}
void loop() {
	char caracter;
	caracter = teclado.comprueba(); // Comprueba el teclado
	if (caracter) // Si se pulsó el teclado ...
		pantalla.escribeCaracter(caracter); // visualiza el carácter
}