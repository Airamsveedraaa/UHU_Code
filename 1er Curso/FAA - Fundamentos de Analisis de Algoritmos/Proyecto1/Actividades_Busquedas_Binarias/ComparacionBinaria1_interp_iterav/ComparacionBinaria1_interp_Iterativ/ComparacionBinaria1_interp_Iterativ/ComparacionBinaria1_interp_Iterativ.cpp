#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <iomanip>

using namespace std;

//Variables globales para contar operaciones elementales de las versiones iterativas
int OE_ITER_BN = 0;     //Para BÚSQUEDABINARIA1
int OE_ITER_INTER = 0;  // Para BÚSQUEDABINARIAINTERPOLACIÓN



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

int BusquedaBinariaIterativa3(int A[], int n, int x) {
    OE_ITER_INTER += 3; // Inicialización de izq y der
    int izq = 0;
    int der = n - 1;

    OE_ITER_INTER += 1; // Condición del while
    while (izq <= der) {
        int pos;
        if (A[der] == A[izq]) { // Evitar división por cero
            OE_ITER_INTER += 6; // Comparación y cálculo de pos
            pos = (izq + der) / 2;
        }
        else {
            OE_ITER_INTER += 10; // Cálculo de pos
            pos = izq + ((x - A[izq]) * (der - izq)) / (A[der] - A[izq]);
        }

        if (pos < izq || pos > der) {
            OE_ITER_INTER += 6; // Comparación y ajuste de pos
            pos = (izq + der) / 2;
        }

        if (A[pos] == x) {
            OE_ITER_INTER += 2; // Comparación y retorno
            return pos;
        }
        else if (A[pos] > x) {
            OE_ITER_INTER += 4; // Comparación y actualización de der
            der = pos - 1;
        }
        else {
            OE_ITER_INTER += 2; // Comparación y actualización de izq
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
    else if (distribucion == "exponencial") {
        exponential_distribution<> dis(1.0);
        for (int i = 0; i < tam; ++i) {
            // Escalar y convertir a entero
            int valor = static_cast<int>(dis(gen) * 100000);
            v.push_back(valor);
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
        OE_ITER_BN = 0;
        OE_ITER_INTER = 0;

        // Medir tiempo Iterativo1
        auto start_iter1 = chrono::high_resolution_clock::now();
        BusquedaBinariaIterativa1(datos, 0, x);
        auto end_iter1 = chrono::high_resolution_clock::now();
        double tiempo_iter1 = chrono::duration<double>(end_iter1 - start_iter1).count();


        // Medir tiempo IterativoInterpolacion
        auto start_iterInterp = chrono::high_resolution_clock::now();
        BusquedaBinariaIterativa3(datos, 0, x);
        auto end_iterInterp = chrono::high_resolution_clock::now();
        double tiempo_iterInterp = chrono::duration<double>(end_iterInterp - start_iterInterp).count();

        // Escribir resultados
        archivo << n << ";" << distribucion <<
            ";" << OE_ITER_BN << ";" << OE_ITER_INTER << ";"
            << fixed << setprecision(8) << tiempo_iter1 << ";" << tiempo_iterInterp << "\n";
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
        OE_ITER_BN = 0;
        OE_ITER_INTER = 0;

        // Medir tiempo Iterativo1
        auto start_iter1 = chrono::high_resolution_clock::now();
        BusquedaBinariaIterativa1(datos, n, x);
        auto end_iter1 = chrono::high_resolution_clock::now();
        double tiempo_iter1 = chrono::duration<double>(end_iter1 - start_iter1).count();


        // Medir tiempo IterativoInterpolacion
        auto start_iterInterp = chrono::high_resolution_clock::now();
        BusquedaBinariaIterativa3(datos, n, x);
        auto end_iterInterp = chrono::high_resolution_clock::now();
        double tiempo_iterInterp = chrono::duration<double>(end_iterInterp - start_iterInterp).count();

        // Escribir resultados
        archivo << n << ";" << distribucion <<
            ";" << OE_ITER_BN << ";" << OE_ITER_INTER << ";"
            << fixed << setprecision(8) << tiempo_iter1 << ";" << tiempo_iterInterp << "\n";
    }
}

int main() {
    const unsigned int semilla = 12345;
    ofstream archivo("resultados.csv");

    // Encabezados del CSV
    archivo << "Tamano;Distribucion;OE_Iter1;OE_IterInterp;Tiempo_iter1(s);Tiempo_iter_interp\n";

    // Prueba específica para array vacío
    vector<int> vacio;
    realizarPruebas(vacio, "vacio", archivo);

    // Tamaños originales para uniforme y gaussiana
    vector<int> tamanos_originales = { 1000, 10000, 100000, 1000000, 10000000 };

    // Tamaños como potencias de 2 para exponencial
    vector<int> tamanos_exponencial;
    for (int i = 10; i <= 23; ++i) {
        tamanos_exponencial.push_back(1 << i);
    }

    // Probar distribuciones uniforme y gaussiana con tamaños originales
    for (int tam : tamanos_originales) {
        vector<int> v;
        generarVector(v, tam, "uniforme", semilla);
        realizarPruebas(v, "uniforme", archivo);
    }

    for (int tam : tamanos_originales) {
        vector<int> v;
        generarVector(v, tam, "gaussiana", semilla);
        realizarPruebas(v, "gaussiana", archivo);
    }

    // Probar distribución exponencial con tamaños de potencias de 2
    for (int tam : tamanos_exponencial) {
        vector<int> v;
        generarVector(v, tam, "exponencial", semilla);
        realizarPruebas(v, "exponencial", archivo);
    }

    archivo.close();
    cout << "Pruebas completadas. Resultados en 'resultados.csv'\n";
    return 0;
}