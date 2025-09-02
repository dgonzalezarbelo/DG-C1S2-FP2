#include <iostream>
#include "JuegoPM.h"

void mainPuzzlesReunidos() {
	tPuzzlesReunidos jr;
	bool ok, conseguido, insertado, cargado, desordenado = false;
	int num, tipo, opcion;
	inicializar(jr);
	opcion = menu();
	while (opcion != 0) {
		std::cin.ignore();
		borrar();
		if (opcion != 3) {
			do {
				num = elegirPuzzle(jr[opcion - 1], (std::to_string(opcion) + 'D'));
				if (num == -1) {	//Si la opción es -1 mostramos la lista ordenada de mayor a menor
					std::sort(jr[opcion - 1].puzzles, jr[opcion - 1].puzzles + jr[opcion - 1].cont, comparaPuzzlesMayor());
					borrar();
					desordenado = true;
				}
				else if (num == -2) {	//Si la opción es -1 mostramos la lista ordenada de menor a mayor
					std::sort(jr[opcion - 1].puzzles, jr[opcion - 1].puzzles + jr[opcion - 1].cont, comparaPuzzlesMenor());
					borrar();
				}
			} while (num == -1 || num == -2);
			if (num != 0) {
				ok = cargar(*(jr[opcion - 1].puzzles[num - 1]), jr[opcion - 1].puzzles[num - 1]->tipo);	//Volvemos a cargar el puzzle por si los datos se han modificado anteriormente
				if (ok) {
					mainPuzzle(jr[opcion - 1].puzzles[num - 1]);
				}
				pausa();
				borrar();
				if (desordenado) {	//Devolvemos el orden normal a la lista en caso de que se haya ordenado de otra forma
					std::sort(jr[opcion - 1].puzzles, jr[opcion - 1].puzzles + jr[opcion - 1].cont, comparaPuzzlesMenor());
					desordenado = false;
				}
				opcion = menu();
			}
			else {
				borrar();
				if (desordenado) {
					std::sort(jr[opcion - 1].puzzles, jr[opcion - 1].puzzles + jr[opcion - 1].cont, comparaPuzzlesMenor());
					desordenado = false;
				}
				opcion = menu();
			}
		}
		else {	//Si la opción es 3
			tPuzzle* nuevoPuzzle = new tPuzzle;	//Creamos el nuevo puzzle con la información que le pediremos al usuario para parárselo a la función insertarOrdenado
			for (int i = 0; i < numOpciones; i++) {
				mostrarPuzzles(jr[i], std::to_string(i + 1) + 'D');
			}
			std::cout << "Introduzca el nombre del puzzle: ";
			std::getline(std::cin, nuevoPuzzle->nombrePuzzle);
			std::cout << '\n' << "Introduzca el nombre del fichero: ";
			std::cin >> nuevoPuzzle->nombreFichero;
			std::cout << '\n' << "Introduzca el tipo de puzzle (1 = 1D, 2 = 2D): ";
			std::cin >> tipo;
			nuevoPuzzle->tipo = std::to_string(tipo) + 'D';
			cargado = cargar(*nuevoPuzzle, nuevoPuzzle->tipo);
			if (cargado) {	//En caso de cargarse correctamente intentaremos insertarlo en la lista
				insertado = insertarOrdenado(jr[tipo - 1], nuevoPuzzle);
				if (!insertado)
					std::cout << "No se ha insertado el nuevo puzzle\n";
				else {
					guardar(jr);
					std::cout << "Fichero añadido correctamente.\n";
				}
			}
			mostrarPuzzles(jr[tipo - 1], nuevoPuzzle->tipo);
			nuevoPuzzle = nullptr;
			pausa();
			borrar();
			opcion = menu();
		}
	}
	if (opcion == 0) {
		std::cout << "Hasta la próxima!\n";
		guardar(jr);
		for (int i = 0; i < numOpciones; i++) {
			for (int j = 0; j < jr[i].cont; j++)
				delete jr[i].puzzles[j];
		}
	}
}

int menu() {
	int modo;
	do {
		std::cout << "Seleccione una opción:\n";
		std::cout << "1. Resolver un puzzle 1D\n";
		std::cout << "2. Resolver un puzzle 2D\n";
		std::cout << "3. Añadir un puzzle al catálogo\n";
		std::cout << "0. Salir\n";
		std::cin >> modo;
		if (modo < 0 || modo > 3)
			std::cout << "Opción no válida, introduzca otra opción\n";
	} while (modo < 0 || modo > 3);
	return modo;
}
