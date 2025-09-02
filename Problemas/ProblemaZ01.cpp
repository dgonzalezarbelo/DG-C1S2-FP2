// Nombre del alumno: Daniel González Arbelo
// Usuario del Juez: FP2-DG13


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>



// función que resuelve el problema
bool resolver(std::vector <int> const& a, std::vector <int> const& b, int ini, int fin, int buscado, int & pos) {
    bool encontrado;
    if (ini == fin) {
        pos = ini;
        encontrado = false;
    }
    else {
        int m = (ini + fin - 1) / 2;
        if (b[m] < buscado) return resolver(a, b, m + 1, fin, buscado, pos);
        else if (buscado < b[m]) return resolver(a, b, ini, m, buscado, pos);
        else {
            pos = m;
            encontrado = true;
        }
    }
    return encontrado;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, i = 0, pos;
    bool encontrado = true;
    std::cin >> n;
    std::vector <int> a(n);
    std::vector <int> b(n - 1);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        std::cin >> b[i];
    }
    while (encontrado && i < b.size()) {
        encontrado = resolver(a, b, 0, b.size(), a[i], pos);
        if (encontrado) i++;
    }
    std::cout << a[i] << '\n';
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