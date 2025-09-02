 #include <iostream>
#include <fstream>
#include "ListaPuzzles.h"


void inicializar(tPuzzlesReunidos& jr) {
	for (int i = 0; i < numOpciones; i++)
		jr[i].cont = 0;
	cargar(jr);
}

bool cargar(tPuzzlesReunidos& jr) {
	std::ifstream archivo;
	archivo.open("datosPuzzles.txt");
	if (archivo.is_open()) {
		archivo >> jr[0].cont;
		archivo.ignore(256, '\n');
		for (int j = 0; j < numOpciones; j++) {
			for (int i = 0; i < jr[j].cont; i++) {
				jr[j].puzzles[i] = new tPuzzle;
				getline(archivo, jr[j].puzzles[i]->nombrePuzzle);
				archivo >> jr[j].puzzles[i]->nombreFichero;
				archivo.ignore(256, '\n');
				jr[j].puzzles[i]->tipo = std::to_string(j + 1) + "D";
				cargar(*(jr[j].puzzles[i]), jr[j].puzzles[i]->tipo);
			}
			if (j == 0) {
				archivo >> jr[1].cont;
				archivo.ignore(256, '\n');
			}
		}
		archivo.close();
		return true;
	}
	else return false;
}

void guardar(const tPuzzlesReunidos& listas) {
	std::ofstream archivo;
	archivo.open("datosPuzzles.txt");
	if (archivo.is_open()) {
		for (int j = 0; j < numOpciones; j++) {
			archivo << listas[j].cont << '\n';
			for (int i = 0; i < listas[j].cont; i++) {
				archivo << listas[j].puzzles[i]->nombrePuzzle << '\n' << listas[j].puzzles[i]->nombreFichero << '\n';
			}
		}
	}
	archivo.close();
}

int elegirPuzzle(tListaPuzzles& lp, std::string tipo) {
	int opcion;
	do {
		std::cout << "En esta versión están disponibles los siguientes retos:\n";
		mostrarPuzzles(lp, tipo);
		std::cout << "0 Salir\n";
		std::cout << "-1 Ordenar la lista de mayor a menor\n";
		std::cout << "-2 Ordenar la lista de menor a mayor\n";
		std::cin >> opcion;
		if (opcion < -2 || opcion > lp.cont + 1) {
			borrar();
			std::cout << "Opción no válida\n\n";
		}
	} while (opcion < -2 || opcion > lp.cont + 1);
	return opcion;
}

bool insertarOrdenado(tListaPuzzles& l, tPuzzle*& p) {
	int pos;
	bool encontrado, insertado = false;
	//Buscamos el puzzle en cuestión por si figura ya dentro de la lista, en cuyo caso no habrá que insertarlo, y al mismo tiempo recibiremos la posición en la que debería
	//estar en caso de no encontrarse, la cual utilizaremos a continuación para insertarlo
	encontrado = buscar(l, p, pos, 0, l.cont);	
	if (!encontrado) {
		if (l.cont < maxPuzzles) {
			l.puzzles[l.cont] = p;
			l.cont++;
			for (int i = l.cont; i > pos; i--) {	//Desplazaremos a la derecha en la lista todos los puzzles cuya posición es mayor que pos
				l.puzzles[i] = l.puzzles[i - 1];
			}
			l.puzzles[pos] = p;	//Una vez desplazados insertaremos el puzzle en su posición correspondiente
			insertado = true;
		}
		else
			std::cout << "Se ha alcanzado el número máximo de puzzles\n";
	}
	else
		std::cout << "Este puzzle ya existe\n";
	return insertado;
}

bool buscar(const tListaPuzzles& lista, tPuzzle* puzzle, int& pos, int ini, int fin) {	//Implementamos una búsqueda binaria recursiva
	bool encontrado;
	if (ini == fin) {
		pos = ini;
		encontrado = false;
	}
	else {
		int mitad = (ini + fin - 1) / 2;
		if (comparaPuzzlesMenor()(puzzle, lista.puzzles[mitad]))
			encontrado = buscar(lista, puzzle, pos, ini, mitad);
		else if (comparaPuzzlesMenor()(lista.puzzles[mitad], puzzle))
			encontrado = buscar(lista, puzzle, pos, mitad + 1, fin);
		else {
			pos = mitad;
			encontrado = true;
		}
	}
	return encontrado;
}

void mostrarPuzzles(tListaPuzzles const& lista, std::string tipo) {
	std::cout << "Juegos " << tipo << "\n";
	for (int i = 0; i < lista.cont; i++) {
		std::cout << i + 1 << ' ' << lista.puzzles[i]->nombrePuzzle << " con un máximo de " << lista.puzzles[i]->maxMovimientos << " movimientos\n";
	}
	std::cout << '\n';
}