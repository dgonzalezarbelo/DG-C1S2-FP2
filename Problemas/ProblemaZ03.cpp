// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>




// función que resuelve el problema
bool resolver(std::vector <int> const& a, int elemento, int ini, int fin, int & pos) {
    bool encontrado;
    if (ini == fin) {
        pos = ini;
        encontrado = false;
    }
    else {
        int mitad = (ini + fin - 1) / 2;
        if (a[mitad] < elemento) return resolver(a, elemento, mitad + 1, fin, pos);
        else if (a[mitad] > elemento) return resolver(a, elemento, ini, mitad, pos);
        else {
            pos = mitad;
            encontrado = true;
        }
    }
    return encontrado;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num, pos, i = 0;
    std::cin >> num;
    if (num == 0)
        return false;
    std::vector <int> a(num);
    std::vector <int> b(num);
    for (int i = 0; i < num; i++)
        std::cin >> a[i];
    for (int i = 0; i < num; i++)
        std::cin >> b[i];

    bool encontrado = false;
    while (!encontrado & i < num) {
        encontrado = resolver(a, b[i], 0, num, pos);
        i++;
    }

    // escribir sol
    if (encontrado) std::cout << "SI " << pos << '\n';
    else {
        std::cout << "NO ";
        if (a[0] > b[0]) std::cout << "-1 0\n";
        else {
            if (a[num - 1] < b[num - 1]) std::cout << num - 1 << ' ' << num << '\n';
            else std::cout << pos - 1 << ' ' << pos << '\n';
        }
    }

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