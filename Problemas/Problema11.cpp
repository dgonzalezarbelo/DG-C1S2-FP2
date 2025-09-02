// Daniel González Arbelo
// FP2-DG13


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

const int TM = 100;

struct tObjeto {
    std::string identificador;
    int unidades;
};

using tRegistro = tObjeto[TM];

struct tLista {
    int cont;
    int capacidad;
    tRegistro* registros;
};

void iniciar(tLista& lista) {
    lista.registros = new tRegistro[TM];
    lista.cont = 0;
    lista.capacidad = TM;
}

void destruir(tLista& lista) {
    delete[] lista.registros;
    lista.registros = nullptr;
    lista.cont = 0;
    lista.capacidad = 0;
}

bool buscar(tLista const& lista, std::string nombre, int& pos) {
    pos = 0;
    while (pos < lista.cont && lista.registros[pos]->identificador != nombre)
        ++pos;
    return pos < lista.cont;
}

void aumentarCapacidad(tLista& lista) {
    tRegistro* aux = lista.registros;
    lista.registros = new tRegistro[lista.capacidad * 2];
    for (int i = 0; i < lista.cont; ++i) {
        lista.registros[i]->identificador = aux[i]->identificador;
        lista.registros[i]->unidades = aux[i]->unidades;
    }
    delete[] aux;
    lista.capacidad = lista.capacidad * 2;
}

void resolver(tLista & lista, char op) {
    std::string objeto;
    int cantidad, pos;
    bool encontrado;
    if (op == 'A') {
        std::cin >> objeto;
        std::cin >> cantidad;
        encontrado = buscar(lista, objeto, pos);
        if (encontrado) {
            lista.registros[pos]->unidades += cantidad;
        }
        else {
            if (lista.cont == lista.capacidad)
                aumentarCapacidad(lista);
            lista.registros[lista.cont]->identificador = objeto;
            lista.registros[lista.cont]->unidades = cantidad;
            lista.cont++;
        }
    }
    else if (op == 'R') {
        std::cin >> objeto;
        std::cin >> cantidad;
        buscar(lista, objeto, pos);
        lista.registros[pos]->unidades -= cantidad;
        if (lista.registros[pos]->unidades < 0)
            lista.registros[pos]->unidades = 0;
    }
    else if (op == 'L') {
        for (int i = 0; i < lista.cont; i++)
            std::cout << lista.registros[i]->identificador << ' ' << lista.registros[i]->unidades << '\n';
        std::cout << "---\n";
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    char op;
    std::cin >> op;
    tLista lista;
    iniciar(lista);
    while (op != 'F') {
        resolver(lista, op);
        std::cin >> op;
    }
    destruir(lista);
    return false;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
/*#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif */


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
/*#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif*/

    return 0;
}