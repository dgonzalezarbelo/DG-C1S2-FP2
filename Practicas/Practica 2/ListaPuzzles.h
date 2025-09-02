#ifndef LISTA_PUZZLES_H
#define LISTA_PUZZLES_H

#include <iostream>
#include <string>
#include <algorithm>
#include "Puzzle.h"

const int numOpciones = 2;
const int maxPuzzles = 100;

struct comparaPuzzlesMenor {
	bool operator()(tPuzzle* puzzle1, tPuzzle* puzzle2) {
		if (puzzle1->maxMovimientos == puzzle2->maxMovimientos)
			return (puzzle1->nombrePuzzle < puzzle2->nombrePuzzle);
		else
			return (puzzle1->maxMovimientos < puzzle2->maxMovimientos);
	}
};

struct comparaPuzzlesMayor {
	bool operator()(tPuzzle* puzzle1, tPuzzle* puzzle2) {
		if (puzzle1->maxMovimientos == puzzle2->maxMovimientos)
			return (puzzle1->nombrePuzzle < puzzle2->nombrePuzzle);
		else
			return (puzzle1->maxMovimientos > puzzle2->maxMovimientos);
	}
};

struct tListaPuzzles {
	tPuzzle* puzzles[maxPuzzles];
	int cont;
};

using tPuzzlesReunidos = tListaPuzzles[numOpciones];

/*inicializar:	Pone los contadores de la lista a 0 e invoca a cargar.
*/
void inicializar(tPuzzlesReunidos& jr);

/*cargar:	Carga de archivo la lista de puzzles, cuyos datos son los nombres de los puzzles y los nombres de sus respectivos ficheros.
			Devuelve true si la carga es exitosa y false en caso contrario.
*/
bool cargar(tPuzzlesReunidos& jr);

/*guardar:	Guarda la lista de puzzles en el fichero de los datos.
*/
void guardar(const tPuzzlesReunidos& listas);

/*elegirPuzzle:	Te muestra la lista de puzzles de un tipo y te da la opción de elegir uno de ellos o de mostrar la lista reordenada.
				Devuelve el número de puzzle que selecciones.
*/
int elegirPuzzle(tListaPuzzles& lp, std::string tipo);

/*insertarOrdenado:	Recibe un puzzle aparte de la lista de puzzles, comprueba que el puzzle no exista ya dentro de la lista y, en tal caso, lo añade a la lista
					preservando el orden.
					Devuelve true en caso de que se añada el puzzle y false en caso contrario, que se puede dará en caso de ya estar incluido en la lista.
*/
bool insertarOrdenado(tListaPuzzles & l, tPuzzle*& p);

/*buscar:	Recibe la lista de puzzles, el puzzle que se quiere buscar, el rango de la lista en el que se quiere buscar y la variable pos para devolver la posición
			del puzzle en caso de encontrarlo.
			Devuelve true en caso de encontrarse el puzzle y false en caso contrario.
*/
bool buscar(const tListaPuzzles& lista, tPuzzle* puzzle, int& pos, int ini, int fin);


/*mostrarPuzzles:	Muestra la lisa de puzzles del tipo indicado por la entrada.
*/
void mostrarPuzzles(tListaPuzzles const& lista, std::string tipo);

#endif