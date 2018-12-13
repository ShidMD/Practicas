#include "Consola.h"
Consola consola(32, 33, 34, 35, 36, 37, 38, 22, 23, 24, 25, 26, 27, 28, 29,
	"789s456b123d.0ei");
// Construye un objeto Consola indicándole qué señales de la placa Arduino se utilizan para
// manejar la pantalla y el teclado y los caracteres del teclado
String mensaje1("Real:");
// Mensaje en un objeto de la clase String almacenado en memoria RAM
const char * const mensaje2 = "Con 2 decimales:";
// Mensaje manejado en memoria RAM en una matriz de caracteres
const char mensaje3[] PROGMEM = "Entero:";
const char mensaje4[] PROGMEM = "Introducido:";
// Mensajes manejados en memoria Flash en matrices de caracteres

void setup() {
	int entero;
	float real;
	consola.configura(); // Inicializa la consola
	consola.visualizaString(1, 1, mensaje1);
	// Visualiza mensaje1 a partir de la fila 1 y columna 1 de la pantalla
	real = consola.introduceReal(1, 7, 10);
	// Introduce por teclado un número real de hasta 10 caracteres,
	// mostrándolo en pantalla a partir de la fila 1 y columna 7
	consola.visualizaCadena(2, 1, mensaje2);
	// Visualiza mensaje2 a partir de la fila 2 columna 1
	consola.visualizaReal(2, 18, real, 10, 2);
	// Visualiza el número real a partir de la fila 2 columna 18 utilizando
	// 10 caracteres como máximo y con 2 decimales
	consola.visualizaCadenaFlash(3, 1, mensaje3);
	entero = consola.introduceEntero(3, 9, 5);
	// Visualiza mensaje3 en fila 3 columna 1 e introduce un entero de hasta
	// 5 dígitos en fila 3 columna 9
	consola.visualizaCadenaFlash(4, 1, mensaje4);
	consola.visualizaEntero(4, 14, entero);
	// Visualiza mensaje4 en fila 4 columna 1 y también visualiza un entero en
	// fila 4 columna 14
}
void loop() {
	// Vacío
}