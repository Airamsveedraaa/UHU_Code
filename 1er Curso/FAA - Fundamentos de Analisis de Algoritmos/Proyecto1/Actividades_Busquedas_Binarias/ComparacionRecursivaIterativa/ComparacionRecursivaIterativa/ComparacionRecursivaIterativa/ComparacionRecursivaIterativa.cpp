#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <iomanip>

using namespace std;

// Variables globales para contar operaciones elementales de las versiones recursivas
int OE_BN = 0;     //Para BÚSQUEDABINARIA1
int OE_BIN = 0;    // Para BÚSQUEDABINARIA2
int OE_INTER = 0;  // Para BÚSQUEDABINARIAINTERPOLACIÓN

//Variables globales para contar operaciones elementales de las versiones iterativas
int OE_ITER_BN = 0;     //Para BÚSQUEDABINARIA1
int OE_ITER_BIN = 0;    // Para BÚSQUEDABINARIA2
int OE_ITER_INTER = 0;  // Para BÚSQUEDABINARIAINTERPOLACIÓN


//Búsqueda Binaria estandar (versión 1)
int BusquedaBinaria1(int A[], int izq, int der, int x) {
    OE_BN++;
    if (izq > der)
        return -1;
    else {
        int medio;
        OE_BN += 3;
        medio = (izq + der) / 2;

        OE_BN += 2;
        if (A[medio] == x)
            return medio;
        else if (A[medio] > x) {
            OE_BN += 2;
            return BusquedaBinaria1(A, izq, medio - 1, x);
        }
        else
            OE_BN += 2;
        return BusquedaBinaria1(A, medio + 1, der, x);

    }
}
// Búsqueda Binaria estándar (versión 2)
int BusquedaBinaria2(int A[], int izq, int der, int x) {
    OE_BIN++;
    if (izq > der) {
        return -1;
    }

    OE_BIN += 3;
    int medio = (izq + der) / 2;

    // Verificar si es la primera ocurrencia de x
    OE_BIN += 4;
    if (A[medio] == x && (medio == izq || A[medio - 1] != x)) {
        OE_BIN += 4;
        return medio;
    }
    else if (A[medio] >= x) {
        OE_BIN += 2;
        return BusquedaBinaria2(A, izq, medio - 1, x);
    }
    else {
        OE_BIN += 2;
        return BusquedaBinaria2(A, medio + 1, der, x);
    }
}

// Búsqueda por Interpolación
int BusquedaInterpolacion(int A[], int izq, int der, int x) {
    OE_INTER += 4;
    if (izq > der || x < A[izq] || x > A[der]) {
        OE_INTER += 3;
        return -1;
    }

    // Cálculo de la posición estimada
    OE_INTER += 10;
    int pos;
    if (A[der] == A[izq]) { // Evitar división por cero
        pos = (izq + der) / 2;
        OE_INTER += 3;
    }
    else {
        pos = izq + ((x - A[izq]) * (der - izq)) / (A[der] - A[izq]);
    }

    // Asegurar que la posición esté dentro de los límites
    OE_INTER += 3;
    if (pos < izq || pos > der) {
        pos = (izq + der) / 2;
        OE_INTER += 3;
    }

    OE_INTER += 2;
    if (A[pos] == x) {
        return pos;
    }
    else if (A[pos] > x) {
        OE_INTER += 2;
        return BusquedaInterpolacion(A, izq, pos - 1, x);
    }
    else {
        OE_INTER += 2;
        return BusquedaInterpolacion(A, pos + 1, der, x);
    }
}

int BusquedaBinariaIterativa1(int A[], int n, int x) {
	// Inicializar contadores de operaciones elementales
    OE_ITER_BN += 3;
	int izq = 0;
	int der = n - 1;

    OE_ITER_BN += 1;
	while (izq <= der) {
		OE_ITER_BN += 3;
		int medio = (izq + der) / 2;

		if (A[medio] == x) {
			OE_ITER_BN += 2;
			return medio;
		}
		else if (A[medio] > x) {
			OE_ITER_BN += 4;
			der = medio - 1;
		}
		else {
			OE_ITER_BN += 2;
			izq = medio + 1;
		}
	}
	return -1;
}

int BusquedaBinariaIterativa2(int A[], int n, int x) {

	OE_ITER_BIN += 3;
	int izq = 0;
	int der = n - 1;

	OE_ITER_BIN += 1;
	while (izq <= der) {
		OE_ITER_BIN += 3;
		int medio = (izq + der) / 2;

		if (A[medio] == x && (medio == izq || A[medio - 1] != x)) {
			OE_ITER_BIN += 8;
			return medio;
		}
		else if (A[medio] >= x) {
			OE_ITER_BIN += 4;
			der = medio - 1;
		}
		else {
			OE_ITER_BIN += 2;
			izq = medio + 1;
		}
	}
	return -1;
}

int BusquedaBinariaIterativa3(int A[], int n, int x) {
	OE_ITER_INTER += 3;
	int izq = 0;
	int der = n - 1;

	OE_ITER_INTER += 1;
	while (izq <= der) {
		int pos;
		if (A[der] == A[izq]) { // Evitar división por cero
			OE_ITER_INTER += 6;
			pos = (izq + der) / 2;
		}
		else {
			OE_ITER_INTER += 10;
			pos = izq + ((x - A[izq]) * (der - izq)) / (A[der] - A[izq]);
		}

		if (pos < izq || pos > der) {
			OE_ITER_INTER += 6;
			pos = (izq + der) / 2;
		}

		if (A[pos] == x) {
			OE_ITER_INTER += 2;
			return pos;
		}
		else if (A[pos] > x) {
			OE_ITER_INTER += 4;
			der = pos - 1;
		}
		else {
			OE_ITER_INTER += 2;
			izq = pos + 1;
		}
	}
	return -1;
}

// Función para generar vectores con diferentes distribuciones
void generarVector(vector<int>& v, int tam, const string& distribucion, unsigned int semilla) {
    mt19937 gen(semilla);
    v.clear();

    if (distribucion == "uniforme") {
        uniform_int_distribution<> dis(0, 1000000);
        for (int i = 0; i < tam; ++i) {
            v.push_back(dis(gen));
        }
    }
    else if (distribucion == "gaussiana") {
        normal_distribution<> dis(500000, 100000);
        for (int i = 0; i < tam; ++i) {
            v.push_back(static_cast<int>(dis(gen)));
        }
    }
    sort(v.begin(), v.end());
}



// Función para realizar pruebas y mediciones
void realizarPruebas(const vector<int>& v, const string& distribucion, ofstream& archivo) {
    int n = v.size();
    vector<int> copia = v;
    int* datos = copia.data();

    //Caso especial, array vacio, ya que si se evaluan juntos lanzarán excepciones el copia.front() y copia.back() ya que se encontraría fuera de los límites.
    if (n == 0) {
        int x = 0;
        // Reiniciar contadores
        OE_BN = 0;
        OE_BIN = 0;
        OE_INTER = 0;
		OE_ITER_BN = 0;
		OE_ITER_BIN = 0;
		OE_ITER_INTER = 0;

        // Medir tiempo binario1
        auto start_bin1 = chrono::high_resolution_clock::now();
        BusquedaBinaria1(datos, 0, -1, x);
        auto end_bin1 = chrono::high_resolution_clock::now();
        double tiempo_bin1 = chrono::duration<double>(end_bin1 - start_bin1).count();

        // Medir tiempo Iterativo1
        auto start_iter1 = chrono::high_resolution_clock::now();
        BusquedaBinariaIterativa1(datos, 0, x);
        auto end_iter1 = chrono::high_resolution_clock::now();
        double tiempo_iter1 = chrono::duration<double>(end_iter1 - start_iter1).count();

        // Medir tiempo binario2
        auto start_bin = chrono::high_resolution_clock::now();
        BusquedaBinaria2(datos, 0, -1, x);
        auto end_bin = chrono::high_resolution_clock::now();
        double tiempo_bin = chrono::duration<double>(end_bin - start_bin).count();

        // Medir tiempo Iterativo2
        auto start_iter2 = chrono::high_resolution_clock::now();
        BusquedaBinariaIterativa2(datos, 0, x);
        auto end_iter2 = chrono::high_resolution_clock::now();
        double tiempo_iter2 = chrono::duration<double>(end_iter2 - start_iter2).count();

        // Medir tiempo interpolación
        auto start_inter = chrono::high_resolution_clock::now();
        BusquedaInterpolacion(datos, 0, -1, x);
        auto end_inter = chrono::high_resolution_clock::now();
        double tiempo_inter = chrono::duration<double>(end_inter - start_inter).count();

        // Medir tiempo IterativoInterpolacion
        auto start_iterInterp = chrono::high_resolution_clock::now();
        BusquedaBinariaIterativa3(datos, 0, x);
        auto end_iterInterp = chrono::high_resolution_clock::now();
        double tiempo_iterInterp = chrono::duration<double>(end_iterInterp - start_iterInterp).count();

        // Escribir resultados
        archivo << n << ";" << distribucion << ";"
			<< OE_BN << ";" << OE_ITER_BN << ";" << OE_BIN << ";" << OE_ITER_BIN << ";" << OE_INTER << ";" << OE_ITER_INTER << ";"
            << fixed << setprecision(8) << tiempo_bin1 << ";" << tiempo_iter1 << ";" << tiempo_bin << ";" << tiempo_iter2 << ";" << tiempo_inter << ";" << tiempo_iterInterp << "\n";

        return;

    }

    // Preparar valores a buscar
    vector<int> valores_buscar;

    // 2. Añadir casos estándar (si no son repetidos)
    valores_buscar.push_back(v.front());
    if (v.front() != v.back()) {
        valores_buscar.push_back(v.back());
    }
    valores_buscar.push_back(v[n / 2]);
    valores_buscar.push_back(v.back() + 100); // Valor que no existe


    for (int x : valores_buscar) {
        // Reiniciar contadores
        OE_BN = 0;
        OE_BIN = 0;
        OE_INTER = 0;
		OE_ITER_BN = 0;
		OE_ITER_BIN = 0;
		OE_ITER_INTER = 0;

        // Medir tiempo binario1
        auto start_bin1 = chrono::high_resolution_clock::now();
        BusquedaBinaria1(datos, 0, n-1 , x);
        auto end_bin1 = chrono::high_resolution_clock::now();
        double tiempo_bin1 = chrono::duration<double>(end_bin1 - start_bin1).count();

        // Medir tiempo Iterativo1
        auto start_iter1 = chrono::high_resolution_clock::now();
        BusquedaBinariaIterativa1(datos, n , x);
        auto end_iter1 = chrono::high_resolution_clock::now();
        double tiempo_iter1 = chrono::duration<double>(end_iter1 - start_iter1).count();

        // Medir tiempo binario2
        auto start_bin = chrono::high_resolution_clock::now();
        BusquedaBinaria2(datos, 0, n - 1, x);
        auto end_bin = chrono::high_resolution_clock::now();
        double tiempo_bin = chrono::duration<double>(end_bin - start_bin).count();

        // Medir tiempo Iterativo2
        auto start_iter2 = chrono::high_resolution_clock::now();
        BusquedaBinariaIterativa2(datos, n , x);
        auto end_iter2 = chrono::high_resolution_clock::now();
        double tiempo_iter2 = chrono::duration<double>(end_iter2 - start_iter2).count();

        // Medir tiempo interpolación
        auto start_inter = chrono::high_resolution_clock::now();
        BusquedaInterpolacion(datos, 0, n - 1, x);
        auto end_inter = chrono::high_resolution_clock::now();
        double tiempo_inter = chrono::duration<double>(end_inter - start_inter).count();

        // Medir tiempo IterativoInterpolacion
        auto start_iterInterp = chrono::high_resolution_clock::now();
        BusquedaBinariaIterativa3(datos, n , x);
        auto end_iterInterp = chrono::high_resolution_clock::now();
        double tiempo_iterInterp = chrono::duration<double>(end_iterInterp - start_iterInterp).count();

        // Escribir resultados
        archivo << n << ";" << distribucion << ";"
            << OE_BN << ";" << OE_ITER_BN << ";" << OE_BIN << ";" << OE_ITER_BIN << ";" << OE_INTER << ";" << OE_ITER_INTER << ";"
            << fixed << setprecision(8) << tiempo_bin1 << ";" << tiempo_iter1 << ";" << tiempo_bin << ";" << tiempo_iter2 << ";" << tiempo_inter << ";" << tiempo_iterInterp << "\n";
    }
}

int main() {
    const unsigned int semilla = 12345; // Una sola semilla
    ofstream archivo("resultados.csv");

    // Encabezados del CSV
    archivo << "Tamano;Distribucion;OE_Binaria1;OE_Iter1;OE_Binaria2;OE_Iter2;OE_Interpolacion;OE_IterInterp;Tiempo_Binaria1(s);Tiempo_iter1(s);Tiempo_Binaria2(s);Tiempo_iter2(s);Tiempo_Interpolacion(s);Tiempo_iter_interp\n";



    // Prueba específica para array vacío
    vector<int> vacio;
    realizarPruebas(vacio, "vacio", archivo);

    // Tamaños a probar
    vector<int> tamanos = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000 };
    vector<string> distribuciones = { "uniforme", "gaussiana" };

    // Primero realizar pruebas con la distribución uniforme
    for (int tam : tamanos) {
        vector<int> v;
        generarVector(v, tam, "uniforme", semilla);
        realizarPruebas(v, "uniforme", archivo);
    }

    // Luego realizar pruebas con la distribución gaussiana
    for (int tam : tamanos) {
        vector<int> v;
        generarVector(v, tam, "gaussiana", semilla);
        realizarPruebas(v, "gaussiana", archivo);
    }

    archivo.close();
    cout << "Pruebas completadas. Resultados en 'resultados.csv'\n";
    return 0;
}