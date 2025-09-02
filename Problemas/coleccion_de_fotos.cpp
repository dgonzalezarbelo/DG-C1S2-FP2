// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using tMatrizFoto = std::vector<std::vector<int>>;

struct tFoto {
    std::string titulo;
    std::string tema;
    tMatrizFoto foto;
};

struct ComparaTitulo {
    bool operator()(tFoto* p1, tFoto* p2) {
        return (p1->titulo < p2->titulo);
    }
};

struct ComparaTema {
    bool operator()(tFoto* p1, tFoto* p2) {
        if (p1->tema == p2->tema)
            return (p1->titulo < p2->titulo);
        else
            return (p1->tema < p2->tema);
    }
};

// función que resuelve el problema
void resolver(std::vector <tFoto*>& v1, std::vector <tFoto*>& v2) {
    sort(v1.begin(), v1.end(), ComparaTitulo());
    sort(v2.begin(), v2.end(), ComparaTema());
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int numImagenes;
    std::cin >> numImagenes;
    if (numImagenes == 0)
        return false;
    std::cin.ignore(256, '\n');
    std::vector <tFoto> fotos(numImagenes);
    for (int i = 0; i < numImagenes; i++) {
        fotos[i].foto.resize(50, std::vector<int> (50, i));
    }
    for (int i = 0; i < numImagenes; i++) {
        std::getline(std::cin, fotos[i].titulo);
    }
    for (int i = 0; i < numImagenes; i++) {
        std::getline(std::cin, fotos[i].tema);
    }
    std::vector <tFoto*> v1(numImagenes);
    std::vector <tFoto*> v2(numImagenes);
    for (int i = 0; i < numImagenes; i++) {
        v1[i] = &fotos[i];
        v2[i] = &fotos[i];
    }

    resolver(v1, v2);

    // escribir sol
    for (int i = 0; i < numImagenes; i++) {
        std::cout << v1[i]->titulo << '\n';
    }
    std::cout << '\n';
    for (int i = 0; i < numImagenes; i++) {
        std::cout << v2[i]->tema << " - " << v2[i]->titulo << '\n';
    }
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
