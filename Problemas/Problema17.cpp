// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

int paresDerecha(std::vector <int> v, int fin) {
    if (fin == 1) {
        if ((v[0] % 2) == 0) return 1;
        else return 0;
    }
    else {
        if ((v[fin - 1] % 2) == 0) return (paresDerecha(v, fin - 1) + 1);
        else return paresDerecha(v, fin - 1);
    }
}

int paresIzquierda(std::vector <int> v, int ini) {
    if (ini == v.size() - 1) {
        if ((v[ini] % 2) == 0) return 1;
        else return 0;
    }
    else {
        if ((v[ini] % 2) == 0) return (paresIzquierda(v, ini + 1) + 1);
        else return paresIzquierda(v, ini + 1);
    }
}

int paresMitad(std::vector <int> v, int ini, int fin) {
    if ((fin - ini) <= 1) {
        if ((v[ini] % 2) == 0) return 1;
        else return 0;
    } 
    else return (paresMitad(v, ini, (ini + fin) / 2) + paresMitad(v, (ini + fin) / 2, fin));
}

// función que resuelve el problema

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
    int ini = 0, fin = v.size();
    // escribir sol
    std::cout << paresDerecha(v, fin) << '\n' << paresIzquierda(v, ini) << '\n' << paresMitad(v, ini, fin) << '\n';

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