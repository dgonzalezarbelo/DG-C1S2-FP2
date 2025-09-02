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
    if (rango(mat, pos1, pos2)) { //Si las posiciones no están fuera de rango
        c = mat[pos1.fila][pos1.col];
        mat[pos1.fila][pos1.col] = mat[pos2.fila][pos2.col];
        mat[pos2.fila][pos2.col] = c;
        return true;
    }
    else
        return false;
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
                ok = swap(mat, coor1, coor2);
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
        //coorFinal.fila = coorInicial.fila;
        //coorFinal.col = coorInicial.col;
        /*while (ok) {
            if (coorFinal.fila + 1 < mat.size() && coorFinal.col + 1 < mat[0].size()) {
                coorFinal.fila += 1;
                coorFinal.col += 1;
            }
            else
                ok = false;
        }
        ok = true;*/
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
    bool sol;
    std::string op;
    std::cin >> op;
    if (op == "SD") {
        int d;
        std::cin >> d;
        sol = swapD(mat, d);
    }
    else if (op == "VD") {
        int d;
        std::cin >> d;
        sol = voltearD(mat, d);
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