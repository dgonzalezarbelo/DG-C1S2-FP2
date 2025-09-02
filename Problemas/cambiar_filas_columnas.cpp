// Daniel González Arbelo
// FP2-DG13


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

const int DIM_MAX = 64;

using tMatriz = std::vector<std::vector<unsigned char>>;

struct tCoor {
    int fila;
    int col;
};

bool cargar(tMatriz& mat, std::ifstream& flujo) {
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

bool rango(tMatriz mat, tCoor pos1, tCoor pos2) {
    if (pos1.fila >= 0 && pos1.col >= 0 && pos2.fila >= 0 && pos2.col >= 0) {
        if (pos1.fila < mat.size() && pos1.col < mat[0].size() && pos2.fila < mat.size() && pos2.col < mat[0].size())
            return true;
        else
            return false;
    }
    else
        return false;
}

bool swap(tMatriz& mat, tCoor pos1, tCoor pos2) {
    unsigned char c;
    if (rango(mat, pos1, pos2)) { //Si las posiciones no están fuera de rango
        c = mat[pos1.fila][pos1.col];
        mat[pos1.fila][pos1.col] = mat[pos2.fila][pos2.col];
        mat[pos2.fila][pos2.col] = c;
        return true;
    }
    else
        return false;
}

bool swapF(tMatriz& mat, int f1, int f2) {
    tCoor coor1, coor2;
    int i = 0;
    bool ok = true;
    coor1.fila = f1;
    coor1.col = 0;
    coor2.fila = f2;
    coor2.col = 0;
    if (rango(mat, coor1, coor2)) {   //Si las filas no están fuera de rango
        if (f1 != f2) {
            //unsigned char aux;
            while (i < mat[0].size() && ok) {
                ok = swap(mat, coor1, coor2);
                coor1.col++;
                coor2.col++;
                i++;
            }
            /*for (int i = 0; i < mat[0].size(); i++) {
                aux = mat[f1][i];
                mat[f1][i] = mat[f2][i];
                mat[f2][i] = aux;
            }*/
        }
        return true;
    }
    else
        return false;
}

bool swapC(tMatriz& mat, int c1, int c2) {
    tCoor coor1, coor2;
    int i = 0;
    bool ok = true;
    coor1.fila = 0;
    coor1.col = c1;
    coor2.fila = 0;
    coor2.col = c2;
    if (rango(mat, coor1, coor2)) {   //Si las columnas no están fuera de rango
        if (c1 != c2) {
            //unsigned char aux;
            while (i < mat.size() && ok) {
                ok = swap(mat, coor1, coor2);
                coor1.fila++;
                coor2.fila++;
                i++;
            }
            /*for (int i = 0; i < mat.size(); i++) {
                aux = mat[i][c1];
                mat[i][c1] = mat[i][c2];
                mat[i][c2] = aux;
            }*/
        }
        return true;
    }
    else
        return false;
}

void leer(tMatriz& matriz) {
    for (int f = 0; f < matriz.size(); ++f)
        for (int c = 0; c < matriz[f].size(); ++c)
            std::cin >> matriz[f][c];
}

void mostrar(tMatriz const& matriz) {
    for (int f = 0; f < matriz.size(); ++f) {
        for (int c = 0; c < matriz[f].size(); ++c)
            std::cout << matriz[f][c] << ' ';
        std::cout << '\n';
    }
}

//En el juez: ok = bool cargar(m, std::cin)
//En la práctica el flujo vendrá de archivo

// función que resuelve el problema
bool resolver(tMatriz& mat) {
    bool sol;
    std::string op;
    std::cin >> op;
    if (op == "SF") {
        int f1, f2;
        std::cin >> f1 >> f2;
        sol = swapF(mat, f1, f2);
    }
    else if (op == "SC") {
        int c1, c2;
        std::cin >> c1 >> c2;
        sol = swapC(mat, c1, c2);
    }
    return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int numFilas, numCols, numOp;
    std::cin >> numFilas >> numCols;
    tMatriz mat(numFilas, std::vector<unsigned char> (numCols));
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