// Nombre del alumno: Daniel González Arbelo
// Usuario del Juez: FP2-DG13


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>




// función que resuelve el problema
std::string resolver(int num) {
    if (num == 1) {
        std::string sol;
        sol = std::to_string(num);
        return sol;
    }
    else if (num == 0) {
        std::string sol = std::to_string(num);
        return sol;
    }
    else return (resolver(num / 2) + std::to_string(num % 2));
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num;
    std::cin >> num;
    if (!std::cin)
        return false;

    std::string sol = resolver(num);

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