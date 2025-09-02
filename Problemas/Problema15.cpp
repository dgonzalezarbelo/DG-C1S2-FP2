// Nombre del alumno: Daniel González Arbelo
// Usuario del Juez: FP2-DG13


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

struct sol {
    int numero;
    int pot;
};


// función que resuelve el problema
sol invertir(int num) {
    sol solucion;
    if (num < 10) return { num, 10 };
    else {
        solucion = invertir(num / 10);
        solucion.numero += (num % 10) * solucion.pot;
        solucion.pot *= 10;
    }
    return solucion;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num;
    std::cin >> num;
    if (!std::cin)
        return false;

    sol solucion = invertir(num);

    // escribir sol
    std::cout << solucion.numero << '\n';

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}