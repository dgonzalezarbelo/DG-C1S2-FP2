// Daniel González Arbelo
// FP2-DG13


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


// función que resuelve el problema
int resolver(vector<int> const& v, int pos) {
    int pareja = -1;
    if (v[pos] == v[pos + 1])
        pareja = pos;
    return pareja;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso(int pos) {
    // leer los datos de la entrada
    int numElem, pos;
    cin >> numElem;
    vector<int> v(numElem);
    for (int& x : v) {
        cin >> x;
    }
    sort(v.begin(), v.end());

    int sol = resolver(v, pos);
    // escribir sol
    if(sol != -1)
        cout << sol << endl;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream archivo("datos.txt");
    auto cinbuf = std::cin.rdbuf(archivo.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    archivo >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso(i);


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}