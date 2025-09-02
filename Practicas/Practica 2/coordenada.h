//Alumno: Daniel González Arbelo

#ifndef COORDENADA_H
#define COORDENADA_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct tCoor {
    int fila;
    int col;
};

bool operator == (tCoor const& pos1, tCoor const& pos2); //Devuelve true si las dos coordenadas son idénticas

bool operator != (tCoor const& pos1, tCoor const& pos2); //Devuelve true si las dos coordenadas tienen alguna diferencia

tCoor operator + (tCoor const& pos1, tCoor const& pos2); //Devuelve la coordenada resultante de sumar las dos de entrada componente a componente

#endif
