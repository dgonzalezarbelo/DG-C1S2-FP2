// Daniel González Arbelo
// FP2-DG13


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

const int DIM_MAX = 64;

using tMatrizChar = std::vector<std::vector<unsigned char>>;

struct tCoor {
    int fila;
    int col;
}; 
const int NumDirecciones = 8;   //Las posiciones adyacentes a cualquier posición dentro de una matriz

typedef tCoor tMatrizAdyacencia[NumDirecciones];


bool cargar(tMatrizChar& mat, std::ifstream& flujo) {
    bool ok = flujo.fail(); int fila = 0;
    while (fila < mat.size() && ok) {
        int col = 0;
        while (col < mat[fila].size() && ok) {
            flujo >> mat[fila][col];
            if (flujo.fail()) ok = false;
            else ++col;
        }
        if (ok) ++fila;
    }
    return ok;
}

bool operator == (tCoor const& pos1, tCoor const& pos2) {
    return ((pos1.fila == pos2.fila) && (pos1.col == pos2.col));
}

tCoor operator + (tCoor const& pos1, tCoor const& pos2) {
    tCoor aux;
    aux.fila = pos1.fila + pos2.fila;
    aux.col = pos1.col + pos2.col;
    return aux;
}

bool rango(tMatrizChar mat, tCoor pos1, tCoor pos2) {
    if (pos1.fila >= 0 && pos1.col >= 0 && pos2.fila >= 0 && pos2.col >= 0) {
        if (pos1.fila < mat.size() && pos1.col < mat[0].size() && pos2.fila < mat.size() && pos2.col < mat[0].size())
            return true;
        else
            return false;
    }
    else
        return false;
}

bool swap(tMatrizChar& mat, tCoor pos1, tCoor pos2) {
    unsigned char c;
    c = mat[pos1.fila][pos1.col];
    mat[pos1.fila][pos1.col] = mat[pos2.fila][pos2.col];
    mat[pos2.fila][pos2.col] = c;
    return true;
}

bool swapD(tMatrizChar& mat, int d) {
    int diagonal = d, i = 0;
    tCoor coor1, coor2;
    bool ok = true, bien = false;
    if (mat.size() == mat[0].size()) {
        if (diagonal < 0)
            diagonal = 0 - diagonal;
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
                if (rango(mat, coor1, coor2)) {
                    ok = swap(mat, coor1, coor2);
                }
                if (ok)
                    bien = true;
                i++;
            }
        }
        else
            bien = true;
    }
    return bien;
}

bool voltearD(tMatrizChar& mat, int d) {
    int longD, i = 0, iteraciones = -1;     //Inicializamos iteraciones a un valor distinto de 0 para que si la matriz no es cuadrada al final no devuelva el valor bien = true
    tCoor coorInicial, coorFinal;
    bool ok = true, bien = false;
    if (mat.size() == mat[0].size()) {
        if (d >= 0) {
            coorInicial.fila = 0;
            coorInicial.col = d;
        }

        else {
            coorInicial.fila = 0 - d;
            coorInicial.col = 0;
        }
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

bool swapF(tMatrizChar& mat, int f1, int f2) {
    tCoor coor1, coor2;
    coor1.fila = f1;
    coor1.col = 0;
    coor2.fila = f2;
    coor2.col = 0;
    if (rango(mat, coor1, coor2)) {   //Si las filas no están fuera de rango
        if (f1 != f2) {
            unsigned char aux;
            for (int i = 0; i < mat[0].size(); i++) {
                aux = mat[f1][i];
                mat[f1][i] = mat[f2][i];
                mat[f2][i] = aux;
            }
        }
        return true;
    }
    else
        return false;
}

bool swapC(tMatrizChar& mat, int c1, int c2) {
    tCoor coor1, coor2;
    coor1.fila = 0;
    coor1.col = c1;
    coor2.fila = 0;
    coor2.col = c2;
    if (c1 != c2) {
        unsigned char aux;
        for (int i = 0; i < mat.size(); i++) {
            aux = mat[i][c1];
            mat[i][c1] = mat[i][c2];
            mat[i][c2] = aux;
        }
    }
    return true;
}


void voltearV(tMatrizChar& mat) {
    int c1 = 0, c2 = mat[0].size() - 1;
    for (int i = 0; i < mat[0].size() / 2; i++) {
        swapC(mat, c1, c2);
        c1++;
        c2--;
    }
}

void voltearH(tMatrizChar& mat) {
    int f1 = 0, f2 = mat.size() - 1;
    for (int i = 0; i < mat.size() / 2; i++) {
        swapF(mat, f1, f2);
        f1++;
        f2--;
    }
}

bool voltearID(tMatrizChar& mat) {
    if (mat.size() == mat[0].size()) {
        for (int i = 1; i < mat.size(); i++) {
            swapD(mat, i);
        }
        return true;
    }
    else
        return false;
}

void rotarD(tMatrizChar& mat) {
    tMatrizChar aux(mat[0].size(), std::vector <unsigned char>(mat.size()));
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            aux[j][mat.size() - 1 - i] = mat[i][j];
        }
    }
    mat = aux;
}

bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2) {
    bool solapamiento = false;
    if (pos1.fila > 0 && pos1.fila < mat.size() - 1 && pos1.col > 0 && pos1.col < mat[0].size() - 1
        && pos2.fila > 0 && pos2.fila < mat.size() - 1 && pos2.col > 0 && pos2.col < mat[0].size() - 1) {
        int distX = pos1.col - pos2.col, distY = pos1.fila - pos2.fila;
        if (distX <= 2 && distX >= -2 && distY <= 2 && distY >= -2)
            return false;
        else {
            std::vector <tCoor> aux = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
            for (int i = 0; i < NumDirecciones; i++)
                swap(mat, pos1 + aux[i], pos2 + aux[i]);
            return true;
        }


        /*if (pos2.fila > 0 && pos2.fila < mat.size() - 1 && pos2.col > 0 && pos2.col < mat[0].size() - 1) {
            tMatrizAdyacencia adyacentesPos1 = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
            tMatrizAdyacencia adyacentesPos2 = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
            for (int i = 0; i < NumDirecciones; i++) {
                adyacentesPos1[i] = pos1 + adyacentesPos1[i];
                adyacentesPos2[i] = pos2 + adyacentesPos2[i];
            }
            for (int i = 0; i < NumDirecciones; i++) {
                for (int j = 0; j < NumDirecciones; j++) {
                    if (adyacentesPos1[i] == adyacentesPos2[j])
                        solapamiento = true;
                }
            }
            if (!solapamiento) {
                for (int i = 0; i < NumDirecciones; i++) {
                    swap(mat, adyacentesPos1[i], adyacentesPos2[i]);
                }
                return true;
            }
            else
                return false;
        }
        else
            return false;*/
    }
    else
        return false;
}






void leer(tMatrizChar& matriz) {
    for (int f = 0; f < matriz.size(); ++f)
        for (int c = 0; c < matriz[f].size(); ++c)
            std::cin >> matriz[f][c];
}

void mostrar(tMatrizChar const& matriz) {
    for (int f = 0; f < matriz.size(); ++f) {
        for (int c = 0; c < matriz[f].size(); ++c)
            std::cout << matriz[f][c] << ' ';
        std::cout << '\n';
    }
}

//En el juez: ok = bool cargar(m, std::cin)
//En la práctica el flujo vendrá de archivo

// función que resuelve el problema
bool resolver(tMatrizChar& mat) {
    bool sol = true;
    std::string op;
    std::cin >> op;
    if (op == "SA") {
        tCoor pos1, pos2;
        std::cin >> pos1.fila >> pos1.col >> pos2.fila >> pos2.col;
        sol = swapAdy(mat, pos1, pos2);
    }
    return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int numFilas, numCols, numOp;
    std::cin >> numFilas >> numCols;
    tMatrizChar mat(numFilas, std::vector<unsigned char>(numCols));
    leer(mat);
    std::cin >> numOp;
    for (int i = 0; i < numOp; i++) {
        bool sol = resolver(mat);
        if (!sol)
            std::cout << "DATOS INCORRECTOS" << '\n';
    }
    mostrar(mat);
    std::cout << "---" << '\n';
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}