// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>




// función que resuelve el problema
int resolver(std::vector <int> const& v, int ini, int fin) {
    if (ini == fin - 1) return v[ini];
    else {
        int m = (ini + fin - 1) / 2;
        if (v[m] < v[m + 1]) return v[m];
        else if (v[0] < v[m]) return resolver(v, ini, m);
        else return resolver(v, m + 1, fin);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num;
    std::cin >> num;
    if (!std::cin)
        return false;
    std::vector <int> v(num);
    for (int i = 0; i < num; i++)
        std::cin >> v[i];


    std::cout << resolver(v, 0, v.size()) << '\n';

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