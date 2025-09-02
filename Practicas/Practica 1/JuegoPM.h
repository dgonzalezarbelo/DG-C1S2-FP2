//Alumno: Daniel González Arbelo

#ifndef JUEGOPM_H
#define JUEGOPM_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "matriz.h"
#include <Windows.h>
#include "UtilidadesSys.h"

struct tJuegoPM {
	tMatrizChar imagen;
	tMatrizChar imObjetivo;
	unsigned int maxAcciones;
	unsigned int accionesRestantes;
	std::string modo;
	std::string nombreFichero;
};

void mainJuegoPM();	//Se encarga de controlar todo el juego
int menu();	//Pide al usuario que elija el modo de juego que quiera seleccionar (Salir, 1D o 2D), y devuelve el modo seleccionado
bool iniciar(tJuegoPM& jpm, std::string modo);	//Guarda el modo de juego e invoca a cargarJPM para la carga de datos (y devuelve lo que devuelva cargarJPM)
bool cargarJPM(tJuegoPM& jpm);	//Se encarga de cargar los datos necesarios para el juego, y devuelve true si logra cargarlos correctamente
void mostrar(tJuegoPM const& jpm);	//Enseña por pantalla el estado actual de la partida y el número de acciones restantes
bool jugar(tJuegoPM& jpm);	//Controla el número de acciones restantes, invoca a acción y devuelve true si se ha logrado el objetivo y false en caso contrario
void accion(tJuegoPM& jpm);	//Pide al usuario que elija que acción quiere realizar sobre la imagen e invoca a la función correspondiente

#endif
