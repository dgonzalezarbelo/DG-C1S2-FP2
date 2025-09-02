//Alumno: Daniel González Arbelo

#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "coordenada.h"

using tMatrizChar = std::vector<std::vector<unsigned char>>;

const int NumDirecciones = 8;   //Las posiciones adyacentes a cualquier posición dentro de una matriz

typedef tCoor tMatrizAdyacencia[NumDirecciones];

/*cargar:	Encargada de introducir en la matriz los datos recogidos en archivo
			Devolverá true si se logra rellenar la matriz por completo
*/
bool cargar(tMatrizChar& mat, std::ifstream& flujo);

/*rango:	Recibe dos posiciones (tCoor) y comprueba que estén dentro de la matriz
			Devuelve true en caso de que lo estén y false en caso contrario
*/
bool rango(tMatrizChar mat, tCoor pos1, tCoor pos2);

/*swap:		Recibe dos posiciones (tCoor) e intercambia el contenido de la matriz en dichas posiciones
			Invoca a rango y por tanto devuelve true si las posiciones están dentro de rango y false en caso contrario
*/
bool swap(tMatrizChar& mat, tCoor pos1, tCoor pos2);

/*swapF:	Recibe dos filas e intercambia el contenido de ambas filas
			Devuelve true si se pueden intercambiar y false en caso contario, que se da si una de las filas está fuera de rango
*/
bool swapF(tMatrizChar& mat, int f1, int f2);

/*swapC:	Recibe dos columnas e intercambia el contenido de ambas columnas
			Devuelve true si se pueden intercambiar y false en caso contario, que se da si una de las columnas está fuera de rango
*/
bool swapC(tMatrizChar& mat, int c1, int c2);

/*swapD:	Recibe una diagonal e intercambia su contenido con el de su diagonal simétrica son respecto a la diagonal principal (-d)
			Devuelve true si se pueden intercambiar y false en caso contrario, que se da si la diagonal está fuera de rango o si la matriz no es cuadrada
*/
bool swapD(tMatrizChar& mat, int d);

/*voltearF:	Recibe una fila e intercambia cada elemento de esa fila con su simétrico con respecto al centro de la fila
			Devuelve true si se pueden hacer los intercambios y false en caso contrario, que se da cuando la fila está fuera de rango
*/
bool voltearF(tMatrizChar& mat, int f);

/*voltearC:	Recibe una columna e intercambia cada elemento de esa columna con su simétrico con respecto al centro de la columna
			Devuelve true si se pueden hacer los intercambios y false en caso contrario, que se da cuando la columna está fuera de rango
*/
bool voltearC(tMatrizChar& mat, int c);

/*voltearD:	Recibe una diagonal e intercambia cada elemento de esa diagonal con su simétrico con respecto al centro de la diagonal
			Devuelve true si se pueden hacer los intercambios y false en caso contrario, que se da cuando la diagonal está fuera de rango
*/
bool voltearD(tMatrizChar& mat, int d);

/*voltearV:	Da la vuelta a la matriz alrededor de su horizontal media
*/
void voltearV(tMatrizChar& mat);

/*voltearH:	Da la vuelta a la matriz alrededor de su vertical media
*/
void voltearH(tMatrizChar& mat);

/*rotarD:	Rota la matriz en sentido horario 90º
			Para ello se utiliza una matriz auxiliar en la que se copian los elementos de mat reordenados con una regla que hace que el resultado sea la rotación de mat
*/
void rotarD(tMatrizChar& mat);

/*swapAdy:	Recibe dos coordenadas e intercambia las ocho posiciones de cada una de ellas por las de la otra
			Devuelve true si se pueden hacer los intercambios y false en caso contrario, que se da cuando alguna de las posiciones está fuera de rango,
			cuando alguna de las posiciones está en el borde de la matriz (y por tanto no tiene adyacentes por algún lado) o cuando se produce solapamiento
			entre las posiciones adyacentes de ambas, es decir, comparten alguna adyacencia
*/
bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2);

/*VoltearID:Da la vuelta a la matriz alrededor de su diagonal principal.
			Devuelve true cuando se puede aplicar la operación y false en caso contrario, que se da cuando la matriz no es cuadrada
*/
bool VoltearID(tMatrizChar& mat);

#endif
