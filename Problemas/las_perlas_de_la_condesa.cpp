// Daniel González Arbelo
// FP2-DG13


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


// función que resuelve el problema
bool resolver(vector<int>& v) {
    bool posible = true;
    string sol;
    sort(v.begin(), v.end());
    if (v.size() % 2 == 1) { //Si el número de perlas es impar (puede haber una más grande que todas las demás)
        for (int i = 0; i < v.size() - 1; i++) { //Queremos comprobar si hay pareja en todos los casos menos en la última posición
            if (v[i] == v[i + 1]) {
                if (i > 0)
                    if (v[i] == v[i - 1]) //Si no es estrictamente mayor (menor no puede ser porque el vector está ordenado de forma creciente)
                        posible = false;
            }
            else
                posible = false;
            i++; //Queremos ir de dos en dos posiciones para no repetir parejas. En caso de que no haya pareja en una posición da igual saltarse una posición distinta, ya sabremos que no es posible
        }
    }
    else
        posible = false;
    return posible;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int primerNum, num, i = 1;
    cin >> primerNum;
    char aux;
    vector<int> v;
    if (primerNum == 0)
        return false;
    else {
        v.push_back(primerNum);
        cin.get(aux);
        while (aux != '\n') {
            cin >> num;
            if (num != 0)
                v.push_back(num);
            cin.get(aux);
            i++;
        }
    }
    bool sol = resolver(v);
    // escribir sol
    if (sol) {
        for (int j = 0; j < v.size(); j = j + 2) {
            cout << v[j] << " ";
        }
        for (int j = v.size() - 3; j >= 0; j = j - 2) {
            cout << v[j] << " ";
        }
        cout << endl;
    }
    else
        cout << "NO" << endl;
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso()) {
    }
    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
