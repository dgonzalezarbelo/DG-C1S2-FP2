// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

const int MaxNumeros = 500000;
const int MayorNumero = 1000000000;

// función que resuelve el problema
void resolver(std::vector<int> conj1, std::vector<int> conj2) {
    /*for (int i = 0, j = 0; i < conj1.size() && j < conj2.size(); i++, j++) {
        if (conj1[i] == conj2[j])
            std::cout << " " << conj1[i];
        else if (conj1[i] < conj2[j])
            j--;
        else
            i--;
    }*/
    int i = 0, j = 0, cont = 0;
    std::vector<int> v;
    while (i < conj1.size() && j < conj2.size()) {
        if (conj1[i] < conj2[j]) 
            i++;
        else if (conj1[i] > conj2[j])
            j++;
        else {
            v.push_back(conj1[i]);
            i++;
            j++;
        }
    }
    for (int x : v) {
        if (cont != 0)
            std::cout << " ";
        std::cout << x;
        cont++;
    }
    std::cout << '\n';
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int num, cont = 0;
    bool fin = false;
    std::vector<int> conj1;
    std::vector<int> conj2;

    while (cont < MaxNumeros && !fin) {
        std::cin >> num;
        if (num > 0)
            conj1.push_back(num);
        else
            fin = true;
    }
    cont = 0;
    fin = false;
    while (cont < MaxNumeros && !fin) {
        std::cin >> num;
        if (num > 0)
            conj2.push_back(num);
        else
            fin = true;
    }
    sort(conj1.begin(), conj1.end());
    sort(conj2.begin(), conj2.end());

    resolver(conj1, conj2);
    //int sol = resolver(conj1, conj2);
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