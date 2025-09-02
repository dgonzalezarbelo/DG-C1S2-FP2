#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <string>
#include "matriz.h"
#include "UtilidadesSys.h"

struct tPuzzle {
	std::string nombrePuzzle;
	std::string nombreFichero;
	std::string tipo;
	int maxMovimientos;
	int movimientosRestantes;
	tMatrizChar imagen;
	tMatrizChar imObjetivo;
};
/*mainPuzzle:	Se encarga de lo relacionado a la resoluci�n del puzzle que recibe.
				Invoca a jugar y muestra por pantalla si se ha logrado compeltar el puzzle o no.
*/
void mainPuzzle(tPuzzle*& puzzle);

/*cargar:	Se encarga de cargar los datos del fichero que corresponde al puzzle que recibe, invocando tambi�n a la funci�n de carga de matrices.
			Devuelve true si la carga es exitosa y false en caso contrario.
*/
bool cargar(tPuzzle& jpm, std::string tipo);

/*mostrar:	Recibe un puzzle y muestra su estado actual por pantalla, aparte del n�mero de acciones restantes.
*/
void mostrar(const tPuzzle& jpm);

/*jugar:	Controla el n�mero de acciones restantes e invoca a acci�n.
			Devuelve true si se ha logrado el objetivo y false en caso contrario.
*/
bool jugar(tPuzzle& jpm);

/*accion:	Pide al usuario que elija la acci�n que quiere realizar sobre la imagen e invoca a la funci�n correspondiente.
*/
void accion(tPuzzle& jpm);

#endif