// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>


struct tProducto {
    std::string identificador;
    int precio;
};

struct comparaPrecios {
    bool operator()(tProducto* prod1, tProducto* prod2) {
        return (prod1->precio > prod2->precio);
    }
};

// función que resuelve el problema
void resolver(std::vector <tProducto*>& vpProductos, int k) {
    bool ultimo = false;
    int precios = 1, productos = 1, i = 1;
    int j = 0;
    sort(vpProductos.begin(), vpProductos.end(), comparaPrecios());
    while (precios <= k && productos < vpProductos.size()) {
        if (vpProductos[i]->precio < vpProductos[i - 1]->precio) {
            precios++;
        }
        if (vpProductos[i]->precio < vpProductos[i - 1]->precio && precios > k) {
        }
        else
            productos++;
        i++;
    }
    for (int j = 0; j < productos; j++) {
        vpProductos[j]->precio -= ((vpProductos[j]->precio % 10) + 1);
    }

    /*for (int i = 0; i < k; i++) {
        vpProductos[i]->precio -= ((vpProductos[i]->precio % 10) + 1);
    }
    while (!ultimo) {
        if (vpProductos[k + j]->precio == vpProductos[k + j - 1]->precio) {
            j++;
        }
        else
            ultimo = true;
    }
    for (int i = 0; i < j; i++) {
        vpProductos[k + i]->precio -= ((vpProductos[k + i]->precio % 10) + 1);
    }*/
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, k;
    std::cin >> n;
    if (!std::cin)
        return false;
    std::cin >> k;
    std::vector <tProducto>vProductos(n);
    std::vector <tProducto*> vpProductos(n);

    for (int i = 0; i < n; i++) {
        std::cin >> vProductos[i].identificador >> vProductos[i].precio;
        vpProductos[i] = &vProductos[i];
    }

    resolver(vpProductos, k);

    // escribir sol
    for (int i = 0; i < n; i++) {
        std::cout << vProductos[i].identificador << ' ' << vProductos[i].precio << '\n';
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