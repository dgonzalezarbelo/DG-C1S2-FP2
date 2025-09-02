// Daniel González Arbelo
// FP2-DG13


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>


struct tHotel {
    std::string nombre;
    int puntuacion;
    int distancia;
    int precio;
};

bool operator > (tHotel const& h1, tHotel const& h2) {
    if (h1.puntuacion == h2.puntuacion)
        return h1.nombre < h2.nombre;
    else
        return h1.puntuacion > h2.puntuacion;
}

struct comparaDistancia {
    bool operator ()(tHotel const& h1, tHotel const& h2) {
        if (h1.distancia == h2.distancia)
            return h1.nombre < h2.nombre;
        else
            return h1.distancia < h2.distancia;
    }
};

struct comparaPrecio {
    bool operator ()(tHotel const& h1, tHotel const& h2) {
        if (h1.precio == h2.precio)
            return h1.nombre < h2.nombre;
        else
            return h1.precio < h2.precio;
    }
};

// función que resuelve el problema
//std::string resolver(std::vector<tHotel> v) {
//}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int numHoteles;
    tHotel hotel;
    std::vector<tHotel> v;
    std::cin >> numHoteles;
    if (!std::cin)
        return false;
    for (int i = 0; i < numHoteles; i++) {
        std::cin >> hotel.nombre >> hotel.puntuacion >> hotel.distancia >> hotel.precio;
        v.push_back(hotel);
    }

    //std::string sol = resolver(v);
    sort(v.begin(), v.end(), std::greater<tHotel>());
    for (int i = 0; i < v.size(); i++)
        std::cout << v[i].nombre << " ";
    std::cout << '\n';
    sort(v.begin(), v.end(), comparaDistancia());
    for (int i = 0; i < v.size(); i++)
        std::cout << v[i].nombre << " ";
    std::cout << '\n';
    sort(v.begin(), v.end(), comparaPrecio());
    for (int i = 0; i < v.size(); i++)
        std::cout << v[i].nombre << " ";
    std::cout << '\n';
    // escribir sol


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