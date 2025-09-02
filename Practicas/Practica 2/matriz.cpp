//Alumno: Daniel González Arbelo

#include <iostream>
#include <vector>
#include <fstream>
#include "coordenada.h"
#include "matriz.h"

const int DIM_MAX = 64;


bool cargar(tMatrizChar& mat, std::istream& flujo) { //La función devolverá true si se logra cargar la matriz acorde a las dimensiones establecidas
    int numFilas, numCols, fila = 0;
    flujo >> numFilas >> numCols;
    mat.resize(numFilas);   //Modificamos el número de filas de la matriz para poder introducir a continuación los valores
    bool ok = !flujo.fail();
    while (fila < numFilas && ok) {
        mat[fila].resize(numCols);  //En cada vuelta del bucle modificamos el tamaño de cada fila para poder introducir el valor de cada casilla
        int col = 0;
        while (col < numCols && ok) {
            flujo >> mat[fila][col];
            if (flujo.fail()) ok = false;   //Seguimos cargando datos en la matriz a no ser que no haya más flujo de entrada
            else ++col;
        }
        if (ok) ++fila;
    }
    return ok;
}

bool rango(tMatrizChar const& mat, tCoor pos1, tCoor pos2) {   //Utilizada para comprobar que un par de coordenadas son válidas de acuerdo a la matriz
    if (pos1.fila >= 0 && pos1.col >= 0 && pos2.fila >= 0 && pos2.col >= 0) 
        return (pos1.fila < mat.size() && pos1.col < mat[0].size() && pos2.fila < mat.size() && pos2.col < mat[0].size());
    else
        return false;
}

bool swap(tMatrizChar& mat, tCoor pos1, tCoor pos2) {
    unsigned char c;
    //Antes de intercambiar las posiciones comprobamos que no estén fuera de rango generalmente se harán 
    //comprobaciones de dimensión antes de invocar a swap, pero es conveniente que la función esa fiable por sí misma
    if (rango(mat, pos1, pos2)) {
        c = mat[pos1.fila][pos1.col];
        mat[pos1.fila][pos1.col] = mat[pos2.fila][pos2.col];
        mat[pos2.fila][pos2.col] = c;
        return true;
    }
    else
        return false;
}

bool swapF(tMatrizChar& mat, int f1, int f2) {
    tCoor coor1, coor2;
    int i = 0;
    bool ok = true;
    coor1 = { f1, 0 };
    coor2 = { f2, 0 };
    if (rango(mat, coor1, coor2)) {   //Si las filas no están fuera de rango
        if (f1 != f2) {
            while (i < mat[0].size() && ok) {
                ok = swap(mat, coor1, coor2);
                coor1.col++;
                coor2.col++;
                i++;
            }
        }
        return true;
    }
    else
        return false;
}

bool swapC(tMatrizChar& mat, int c1, int c2) {
    tCoor coor1, coor2;
    int i = 0;
    bool ok = true;
    coor1.fila = 0;
    coor1.col = c1;
    coor2.fila = 0;
    coor2.col = c2;
    if (rango(mat, coor1, coor2)) {   //Si las columnas no están fuera de rango
        if (c1 != c2) {
            while (i < mat.size() && ok) {
                ok = swap(mat, coor1, coor2);
                coor1.fila++;
                coor2.fila++;
                i++;
            }
        }
        return true;
    }
    else
        return false;
}

bool swapD(tMatrizChar& mat, int d) {
    int diagonal = d, i = 0;
    tCoor coor1, coor2;
    bool ok = true, bien = false;
    if (mat.size() == mat[0].size()) {  //Necesitamos que la matriz sea cuadrada para aplicar la operación
        if (diagonal < 0)
            diagonal = -diagonal;    //Intercambiar una diagonal positiva o negativa es lo mismo, así que trabajamos con la positiva por comodidad
        coor1.fila = 0;
        coor1.col = diagonal;
        coor2.fila = diagonal;
        coor2.col = 0;
        if (d != 0) {
            while (ok && i < mat.size() && i < mat[0].size()) {
                coor1.fila = i;
                coor1.col = diagonal + i;
                coor2.fila = coor1.col;
                coor2.col = coor1.fila;
                ok = swap(mat, coor1, coor2);   //swap comprueba que las coordenadas (las diagonales precisamente) estén dentro de rango
                if (ok) //Si la primera vez ok == true nos garantiza que la operación es exitosa
                    bien = true;
                i++;
            }
        }
        else
            bien = true;
    }
    return bien;
}

bool voltearF(tMatrizChar& mat, int f) {
    tCoor pos1, pos2;
    pos1.fila = f;
    pos2.fila = f;
    int i = 0;
    bool ok = true, res = false;
    do {
        pos1.col = i;
        pos2.col = mat[0].size() - 1 - i;
        ok = swap(mat, pos1, pos2); //Intercambiamos las posiciones opuestas en la fila con respecto al centro
        if (ok) //Si la primera vez ok == true nos garantiza que la operación es exitosa
            res = true;
        i++;
    } while (i <= ((mat[0].size()) / 2) - 1 && ok);
    return res;
}

bool voltearC(tMatrizChar& mat, int c) {
    tCoor pos1, pos2;
    pos1.col = c;
    pos2.col = c;
    int i = 0;
    bool ok = true, res = false;
    do {
        pos1.fila = i;
        pos2.fila = mat.size() - 1 - i;
        ok = swap(mat, pos1, pos2); //Intercambiamos las posiciones opuestas en la columna con respecto al centro
        if (ok) //Si la primera vez ok == true nos garantiza que la operación es exitosa
            res = true;
        i++;
    } while (i <= (mat.size() / 2) - 1 && ok);
    return res;
}

bool voltearD(tMatrizChar& mat, int d) {
    int longD, i = 0, iteraciones = -1;     //Inicializamos iteraciones a un valor distinto de 0 para que si la matriz no es cuadrada al final no devuelva el valor bien = true
    tCoor coorInicial, coorFinal;
    bool ok = true, bien = false;
    if (mat.size() == mat[0].size()) { //Necesitamos que la matriz sea cuadrada para poder aplicar esta operación
        //Primero tomamos como coordenada inicial la primera posición por arriba de la diagonal
        if (d >= 0) 
            coorInicial = { 0, d };
        else 
            coorInicial = { -d, 0 };
        //Según las dimensiones de la matriz calculamos la última posición de la diagonal y el número de intercambios que habrá que realizar
        if ((mat.size() - coorInicial.fila) < (mat[0].size() - coorInicial.col)) {
            coorFinal.fila = mat.size() - 1;
            coorFinal.col = coorFinal.fila - coorInicial.fila;
            iteraciones = (coorFinal.col + 1) / 2;
        }
        else {
            coorFinal.col = mat[0].size() - 1;
            coorFinal.fila = coorFinal.col - coorInicial.col;
            iteraciones = (coorFinal.fila + 1) / 2;
        }
        //Con esto intercambiamos sucesivamente las posiciones opuestas de la diagonal con respecto a su centro
        while (ok && i < iteraciones) {
            ok = swap(mat, coorInicial, coorFinal);
            if (ok)
                bien = true;
            coorInicial.fila++;
            coorInicial.col++;
            coorFinal.fila--;
            coorFinal.col--;
            i++;
        }
    }
    if (iteraciones == 0) { //Por si no hay niguna vuelta del bucle
        tCoor aux;
        aux.fila = 0;
        aux.col = 0;
        if (rango(mat, coorInicial, aux))
            bien = true;
    }
    return bien;
}

void voltearV(tMatrizChar& mat) {
    int c1 = 0, c2 = mat[0].size() - 1;
    for (int i = 0; i < mat[0].size() / 2; i++) { //Intercambiamos sucesivamente las columnas por su opuesta con respecto al centro de la matriz
        swapC(mat, c1, c2);
        c1++;
        c2--;
    }
}

void voltearH(tMatrizChar& mat) {
    int f1 = 0, f2 = mat.size() - 1;
    for (int i = 0; i < mat.size() / 2; i++) { //Intercambiamos sucesivamente las filas por su opuesta con respecto al centro de la matriz
        swapF(mat, f1, f2);
        f1++;
        f2--;
    }
}

void rotarD(tMatrizChar& mat) {
    tMatrizChar aux(mat[0].size(), std::vector <unsigned char>(mat.size()));
    //Calculamos la rotación de mat en una matriz auxiliar
    //Al rotar una posición 90º en sentido horario, la columna final es la fila de partida
    //y la fila final es la columna simétrica a la de partida
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            aux[j][mat.size() - 1 - i] = mat[i][j];
        }
    }
    mat = aux;
}

bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2) {
    bool solapamiento = false;
    //Primero tenemos que comprobar que no haya solapamiento
    //Para ello, si las distancias vertical y horizontal entre ambas posiciones son menores o iguales a dos, habrá solapamiento
    //De lo contrario no lo habrá
    if (pos1.fila > 0 && pos1.fila < mat.size() - 1 && pos1.col > 0 && pos1.col < mat[0].size() - 1
        && pos2.fila > 0 && pos2.fila < mat.size() - 1 && pos2.col > 0 && pos2.col < mat[0].size() - 1) {
        int distX = pos1.col - pos2.col, distY = pos1.fila - pos2.fila;
        if (distX <= 2 && distX >= -2 && distY <= 2 && distY >= -2)
            return false;
        else {
            //Creamos el vector aux con las coordenadas que hay que sumarle a ambas posiciones para obtener sus ocho posiciones adyacentes
            std::vector <tCoor> aux = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
            for (int i = 0; i < NumDirecciones; i++)    //Intercambiamos cada una de las posiciones adyacente de una posición con la de la otra
                swap(mat, pos1 + aux[i], pos2 + aux[i]);
            return true;    //Devolvemos true porque se ha podido hacer el cambio
        }
    }
    else
        return false;
}

bool VoltearID(tMatrizChar& mat) {
    if (mat.size() == mat[0].size()) {  //Es necesario que la matriz sea cuadrada para aplicar esta operación
        for (int i = 1; i < mat.size(); i++) { //Intercambiamos sucesivamente las diagonales con sus simétricas con respecto a la diagonal principal
            swapD(mat, i);  //Partimos de i == 1 porque intercambiar la diagonal principal con su simétrica no produce ningún cambio
        }
        return true;
    }
    else
        return false;
}