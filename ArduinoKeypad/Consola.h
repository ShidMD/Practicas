#include "PantallaMidas.h"
#include "Teclado4x4.h"

class Consola {
 // Un objeto de esta clase representa a una consola compuesta por un teclado y una
 // pantalla
private:
 PantallaMidas pantalla;
 Teclado4x4 teclado;
 // Cada objeto Consola contiene objetos privados para manejar el teclado y la pantalla
public:
	Consola(short k1,short k2,short k3,short k4,short k5,short k6,short k7,short k8,short k9,short k10,short k11, short k12, short k13, short k14, short k15, short k16,const char* caracteres[17]);

	void configura();

	void visualizaString(int fila, int columna, );

	void visualizaReal();

	void visualizaCadena();

	void visualizaCadenaFlash();

	void visualizaEntero();

	void introduceReal();

	void introduceEntero();

}; 
