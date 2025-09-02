// Daniel González Arbelo
// FP2-DG13

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


// función que resuelve el problema
void rellenaArray(std::vector<int> & v, int cuantos) {
    for (int i = 0; i < cuantos; i++)
        std::cin >> v[i];
}

bool busquedaBinaria(std::vector<int> const& array, int const& buscado, size_t& pos) {
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

void resolver(std::vector<int> const& cromosDavid, std::vector<int> const& repetidosDavid, std::vector<int> const& cromosAna, std::vector<int> const& repetidosAna) {
    std::vector<int> paraAna, paraDavid;
    size_t pos;
    for (int i = 0; i < repetidosDavid.size(); i++) {
        if (i > 0) {
            if (repetidosDavid[i] > repetidosDavid[i - 1]) {
                if (!busquedaBinaria(cromosAna, repetidosDavid[i], pos)) {
                    paraAna.push_back(repetidosDavid[i]);
                }
            }
        }
        else {
            if (!busquedaBinaria(cromosAna, repetidosDavid[i], pos)) {
                paraAna.push_back(repetidosDavid[i]);
            }
        }
    }
    for (int i = 0; i < repetidosAna.size(); i++) {
        if (i > 0) {
            if (repetidosAna[i] > repetidosAna[i - 1]) {
                if (!busquedaBinaria(cromosDavid, repetidosAna[i], pos)) {
                    paraDavid.push_back(repetidosAna[i]);
                }
            }
        }
        else {
            if (!busquedaBinaria(cromosDavid, repetidosAna[i], pos)) {
                paraDavid.push_back(repetidosAna[i]);
            }
        }
    }
    for (int i = 0; i < paraAna.size(); i++){
        if(i != 0)
            std::cout << " ";
        std::cout << paraAna[i];
    }

    std::cout << '\n';

    for (int i = 0; i < paraDavid.size(); i++) {
        if (i != 0)
            std::cout << " ";
        std::cout << paraDavid[i];
    }
    std::cout << std::endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int cuantos;
    std::cin >> cuantos;
    std::vector<int> cromosDavid(cuantos);
    rellenaArray(cromosDavid, cuantos);
    std::cin >> cuantos;
    std::vector<int> repetidosDavid(cuantos);
    rellenaArray(repetidosDavid, cuantos);
    std::cin >> cuantos;
    std::vector<int> cromosAna(cuantos);
    rellenaArray(cromosAna, cuantos);
    std::cin >> cuantos;
    std::vector<int> repetidosAna(cuantos);
    rellenaArray(repetidosAna, cuantos);

    sort(repetidosDavid.begin(), repetidosDavid.end());
    sort(repetidosAna.begin(), repetidosAna.end());

    resolver(cromosDavid, repetidosDavid, cromosAna, repetidosAna);
    // escribir sol


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