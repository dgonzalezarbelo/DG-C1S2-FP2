// Nombre del alumno: Daniel González Arbelo
// Usuario del Juez: FP2-DG13


#include <iostream>
#include <iomanip>
#include <fstream>



// función que resuelve el problema
int final(int num, int resto, int potencia) {
    if (num < 10) return (num * 11) * potencia + resto;
    else return final(num / 10, (num % 10) * 11 * potencia + resto, 100*potencia);
}

int noFinal(int num) {
    if (num < 10) return (num * 11);
    else return (noFinal(num / 10) * 100 + 11 * (num % 10));
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int num;
    std::cin >> num;
    std::cout << noFinal(num) << ' ' << final(num, 0, 1) << '\n';
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
/*#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif */


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
/*#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif*/

    return 0;
}