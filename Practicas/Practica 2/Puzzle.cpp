#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "Puzzle.h"
#include "ListaPuzzles.h"
#include "JuegoPM.h"

void mainPuzzle(tPuzzle*& puzzle) {
	bool conseguido;
	conseguido = jugar(*puzzle);
	if (conseguido) {
		std::cout << "Has obtenido la imagen objetivo!!\n";
	}
	else
		std::cout << "No quedan acciones. No has logrado obtener la imagen objetivo!\n";
}

bool cargar(tPuzzle& jpm, std::string tipo) {
	std::ifstream archivo;
	bool ok;
	archivo.open(jpm.nombreFichero);
	ok = archivo.is_open();
	if (ok) {
		ok = cargar(jpm.imagen, archivo);
		if (ok) {
			ok = cargar(jpm.imObjetivo, archivo);
			if (ok) {
				archivo >> jpm.maxMovimientos;
				jpm.movimientosRestantes = jpm.maxMovimientos;
			}
			else
				std::cout << "No se pudieron cargar los datos\n";
		}
		else
			std::cout << "No se pudieron cargar los datos\n";
	}
	else
		std::cout << "No se pudo abrir el archivo\n";
	return ok;
}

void mostrar(tPuzzle const& jpm) {
	std::cout << "  ";	//Mostramos primero dos espacios para alinear los números superiores con la matriz
	//Mostramos el índice de cada columna de la imagen
	for (int i = 0; i < jpm.imagen[0].size(); i++) {
		std::cout << std::right << std::setw(2) << i;
	}
	std::cout << "              ";	//Dejamos espacio para la segunda matriz
	//Mostramos el índice de cada columna de la imagen objetivo
	for (int i = 0; i < jpm.imObjetivo[0].size(); i++) {
		std::cout << std::right << std::setw(2) << i;
	}
	std::cout << '\n';
	//Hacemos un bucle para mostrar cada una de las filas de ambas matrices
	for (int i = 0; i < jpm.imagen.size() || i < jpm.imObjetivo.size(); i++) {
		if (i < jpm.imagen.size())	//Primero mostramos el índice de la fila de la imagen hasta llegar a la última
			std::cout << std::setw(2) << std::right << i;
		else
			std::cout << std::setw(2) << std::right << "  ";
		//Para cada elemento de matriz mostramos por pantalla dos espacios del color que nos indica cada elemento de la fila, o en negro si estamos fuera de rango
		for (int j = 0; j < jpm.imagen[0].size(); j++) {
			if (i >= jpm.imagen.size())
				colorCTA(15, 0);
			else
				colorCTA(15, jpm.imagen[i][j] - '0');
			std::cout << "  ";
			colorCTA(15, 0);
		}
		std::cout << "            ";
		//Repetimos el mismo proceso en cada fila de la imagen objetivo
		if (i < jpm.imObjetivo.size())
			std::cout << std::setw(2) << std::right << i;
		else
			std::cout << std::setw(2) << std::right << "  ";
		for (int k = 0; k < jpm.imObjetivo[0].size(); k++) {
			if (i >= jpm.imObjetivo.size())
				colorCTA(15, 0);
			else
				colorCTA(15, jpm.imObjetivo[i][k] - '0');
			std::cout << "  ";
			colorCTA(15, 0);
			if (k == jpm.imObjetivo[0].size() - 1)
				std::cout << '\n';
		}
	}
	//Debajo de todo mostramos al usuario el número de acciones que le quedan
	std::cout << '\n' << "Quedan " << jpm.movimientosRestantes << " acciones restantes.\n";
}

bool jugar(tPuzzle& jpm) {
	bool conseguido = false;
	while (jpm.movimientosRestantes > 0 && !conseguido) {	//La partida continuará hasta que nos quedemos sin acciones o logremos el objetivo
		accion(jpm);	//Invocamos a la función acción para que el usuario realice el cambio que quiera sobre la imagen
		jpm.movimientosRestantes--;
		mostrar(jpm);	//Una vez realizada la acción mostramos por pantalla el estado actual en el que se encuentra el juego
		if (jpm.imagen == jpm.imObjetivo) {	//Comprobamos si hemos obtenido la imagen objetivo, y en tal caso mostramos por pantalla que hemos logrado el objetivo
			conseguido = true;	//Usaremos esta variable para salir del bucle y dar por terminada la partida
		}
		else
			pausa();
	}
	return conseguido;
}

void accion(tPuzzle& jpm) {
	bool ejecutada, ok, cuadrada = jpm.imagen.size() == jpm.imagen[0].size();	//Usaremos cuadrada para hacer comprobaciones en caso de fallo al aplicar una acción
	std::string opcion;
	do {
		//Primero mostraremos al jugador el estado actual de la partida y las operaciones que puede realizar según el modo de juego seleccionado
		borrar();
		mostrar(jpm);
		std::cout << "Introduzca la acción que quiera ejecutar:\n";
		std::cout << "Opciones:\n";
		if (jpm.tipo == "1D") {
			std::cout << "| Intercambiar filas: SF | Volear fila: VF |\n";
			std::cout << "| Intercambiar columnas: SC | Voltear columna: VC |\n";
			if (cuadrada)	//Para evitar que se intente aplicar la operación sobre una matriz que no la admite
				std::cout << "| Intercambiar diagonales: SD | Voltear diagonal: VD |\n";
		}
		else {
			std::cout << "| Voltear matriz sobre la vertical: VV | Voltear matriz sobre la horizontal: VH |\n";
			std::cout << "| Rotar la matriz 90º hacia la derecha: RD | Intercambiar posiciones adyacentes: SA |\n";
			if (cuadrada)	//Para evitar que se intente aplicar la operación sobre una matriz que no la admite
				std::cout << "| Voltear matriz sobre la diagonal: VD |\n";
		}
		std::cin >> opcion;
		ejecutada = true;
		if (jpm.tipo == "1D") {
			if (opcion == "SF") {
				int f1, f2;
				std::cout << "Introduzca las dos filas que quiera intercambiar (separadas por un espacio): ";
				std::cin >> f1 >> f2;
				std::cout << '\n';
				ok = swapF(jpm.imagen, f1, f2);
				if (!ok) {
					std::cout << "La fila que ha introducido está fuera de rango\n";
					ejecutada = false;
				}
			}
			else if (opcion == "SC") {
				int c1, c2;
				std::cout << "Introduzca las dos columnas que quiera intercambiar (separadas por un espacio): ";
				std::cin >> c1 >> c2;
				std::cout << '\n';
				ok = swapC(jpm.imagen, c1, c2);
				if (!ok) {
					std::cout << "La columna que ha introducido está fuera de rango\n";
					ejecutada = false;
				}
			}
			else if (opcion == "SD") {
				int d;
				if (!cuadrada) {
					std::cout << "Esta imagen no es cuadrada, no le puede aplicar esta operación\n";
					ejecutada = false;
				}
				else {
					std::cout << "Introduzca la diagonal que quiera intercambiar con su simétrica respecto a la principal: ";
					std::cin >> d;
					std::cout << '\n';
					ok = swapD(jpm.imagen, d);
					if (!ok) {	//El único error posible es salirse de rango, pues previamente hemos comprobado ya si la matriz es cuadrada
						std::cout << "La diagonal que ha introducido está fuera de rango\n";
						ejecutada = false;
					}
				}
			}
			else if (opcion == "VF") {
				int f;
				std::cout << "Introduzca la fila que quiera voltear: ";
				std::cin >> f;
				std::cout << '\n';
				ok = voltearF(jpm.imagen, f);
				if (!ok) {
					std::cout << "La fila que ha introducido está fuera de rango\n";
					ejecutada = false;
				}
			}
			else if (opcion == "VC") {
				int c;
				std::cout << "Intruduzca la columna que quiera voltear: ";
				std::cin >> c;
				std::cout << '\n';
				ok = voltearC(jpm.imagen, c);
				if (!ok) {
					std::cout << "La columna que ha introducido está fuera de rango\n";
					ejecutada = false;
				}
			}
			else if (opcion == "VD") {
				int d;
				if (!cuadrada) {
					std::cout << "Esta imagen no es cuadrada, no le puede aplicar esta operación\n";
					ejecutada = false;
				}
				else {
					std::cout << "Introduzca la diagonal que quiera voltear: ";
					std::cin >> d;
					std::cout << '\n';
					ok = voltearD(jpm.imagen, d);
					if (!ok) {	//El único error posible es salirse de rango, pues previamente hemos comprobado ya si la matriz es cuadrada
						std::cout << "La diagonal que ha introducido está fuera de rango\n";
						ejecutada = false;
					}
				}
			}
			else {
				std::cout << "Opción no válida\n";
				ejecutada = false;
			}
		}
		else {
			if (opcion == "VV") {
				voltearV(jpm.imagen);
			}
			else if (opcion == "VH") {
				voltearH(jpm.imagen);
			}
			else if (opcion == "RD") {
				rotarD(jpm.imagen);
			}
			else if (opcion == "SA") {
				tCoor pos1, pos2;
				std::cout << "Introduzca las dos posiciones cuyas adyacentes quiera intercambiar (Formato: Fila1 Columna1 Fila2 Columna2): ";
				std::cin >> pos1.fila >> pos1.col >> pos2.fila >> pos2.col;
				std::cout << '\n';
				ok = swapAdy(jpm.imagen, pos1, pos2);
				if (!ok) {
					std::cout << "Las posiciones que ha introducido no son válidas\n";
					ejecutada = false;
				}
			}
			else if (opcion == "VD") {
				ok = VoltearID(jpm.imagen);
				if (!ok) {
					std::cout << "La imagen no es cuadrada, no le puede aplicar esta operación\n";
					ejecutada = false;
				}
			}
			else {
				std::cout << "Opción no válida\n";
				ejecutada = false;
			}
		}
		if (!ejecutada)
			pausa();
	} while (!ejecutada);
}