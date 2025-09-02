// Daniel González Arbelo
// FP2-DG13


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>


bool buscarBinaria(std::vector<int> const& array, int const& buscado, int& pos) {
    size_t ini = 0, fin = array.size(), mitad;
    bool encontrado = false;
    // 0 <= ini <= fin <= N
    // array[0..ini) < buscado Y buscado < array[fin..N)
    while (ini < fin && !encontrado) {
        mitad = (ini + fin - 1) / 2; // división entera
        if (buscado < array[mitad]) fin = mitad;
        else if (array[mitad] < buscado) ini = mitad + 1;
        else encontrado = true;
    }
    if (encontrado) pos = mitad; // en la posición mitad
    else pos = ini; // No encontrado, le corresponde la posición ini (=fin)
    return encontrado;
}
// función que resuelve el problema
bool resolver(std::vector<int> const& sospechosos, int altura, int& pos) {
    bool encontrado = buscarBinaria(sospechosos, altura, pos);
    bool primero = false;
    int i = pos;

    while (i > 0 && !primero) {
        if (sospechosos[i - 1] == altura)
            pos = i - 1;
        else
            primero = true;
        i--;
    }
    return encontrado;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int cantidad, altura, pos;
    std::cin >> cantidad;
    if (!std::cin)
        return false;
    std::cin >> altura;
    std::vector<int> sospechosos(cantidad);
    for (int i = 0; i < cantidad; i++) {
        std::cin >> sospechosos[i];
    }

    bool sol = resolver(sospechosos, altura, pos);

    // escribir sol
    if (sol)
        std::cout << pos;
    else
        std::cout << "NO EXISTE";
    std::cout << '\n';


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