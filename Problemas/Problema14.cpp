// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>




// función que resuelve el problema
long long int resolver(long long int a) {
    if (a < 10) {
        if ((a % 2) == 0) return 0;
        else return (a % 10);
    }
    else if (a % 2 == 0) return resolver(a / 10);
    else return (10 * resolver(a / 10) + (a % 10));
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    long long int a;
    std::cin >> a;
    if (!std::cin)
        return false;
    long long int sol = resolver(a);

    // escribir sol

    std::cout << sol << '\n';
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