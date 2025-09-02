//Alumno: Daniel González Arbelo

#include "coordenada.h"

bool operator == (tCoor const& pos1, tCoor const& pos2) {
    return ((pos1.fila == pos2.fila) && (pos1.col == pos2.col));
}

bool operator != (tCoor const& pos1, tCoor const& pos2) {
    return (!(pos1 == pos2));
}

tCoor operator + (tCoor const& pos1, tCoor const& pos2) {
    return { pos1.fila + pos2.fila, pos1.col + pos2.col };
}
