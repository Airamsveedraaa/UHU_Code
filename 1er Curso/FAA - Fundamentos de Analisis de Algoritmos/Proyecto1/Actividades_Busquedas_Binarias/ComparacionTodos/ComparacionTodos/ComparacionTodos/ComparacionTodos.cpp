#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <iomanip>

using namespace std;

// Variables globales para contar operaciones elementales
int OE_BN = 0;     //Para BÚSQUEDABINARIA1
int OE_BIN = 0;    // Para BÚSQUEDABINARIA2
int OE_INTER = 0;  // Para BÚSQUEDABINARIAINTERPOLACIÓN


//Búsqueda Binaria estandar (versión 1)
int BusquedaBinaria1(int A[], int izq, int der, int x) {
    OE_BN++;
    if (izq > der)
        return -1;
    else{
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
    else if (distribucion == "repetidos") {
        // Solo generamos 10 valores distintos para asegurar repeticiones
        uniform_int_distribution<> dis(1, 10);
        for (int i = 0; i < tam; ++i) {
            v.push_back(dis(gen));
        }
    }
    sort(v.begin(), v.end());
}


vector<int> obtenerValoresRepetidos(const vector<int>& v) {
    vector<int> repetidos;
    if (v.empty()) return repetidos;

    for (int i = 1; i < v.size(); ++i) {
        if (v[i] == v[i - 1]) {
            // Añadir si es la primera repetición de este valor
            if (repetidos.empty() || v[i] != repetidos.back()) {
                repetidos.push_back(v[i]);
            }
        }
    }
    return repetidos;
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

        // Medir tiempo binario1
        auto start_bin1 = chrono::high_resolution_clock::now();
        BusquedaBinaria1(datos, 0, - 1, x);
        auto end_bin1 = chrono::high_resolution_clock::now();
        double tiempo_bin1 = chrono::duration<double>(end_bin1 - start_bin1).count();

        // Medir tiempo binario2
        auto start_bin = chrono::high_resolution_clock::now();
        BusquedaBinaria2(datos, 0, - 1, x);
        auto end_bin = chrono::high_resolution_clock::now();
        double tiempo_bin = chrono::duration<double>(end_bin - start_bin).count();

        // Medir tiempo interpolación
        auto start_inter = chrono::high_resolution_clock::now();
        BusquedaInterpolacion(datos, 0, - 1, x);
        auto end_inter = chrono::high_resolution_clock::now();
        double tiempo_inter = chrono::duration<double>(end_inter - start_inter).count();
        // Escribir resultados
        archivo << n << ";" << distribucion << ";"
            << OE_BN << ";" << OE_BIN << ";" << OE_INTER << ";"
            << fixed << setprecision(8) << tiempo_bin1 << ";" << tiempo_bin << ";" << tiempo_inter << "\n";

        return;

    }

    // Preparar valores a buscar
    vector<int> valores_buscar;

    // 1. Añadir valores repetidos (si existen)
    vector<int> repetidos = obtenerValoresRepetidos(v);
    if (!repetidos.empty()) {
        // Tomar el primer valor repetido (para probar primera ocurrencia)
        valores_buscar.push_back(repetidos[0]);

        // Si hay múltiples valores repetidos, tomar uno del medio
        if (repetidos.size() > 2) {
            valores_buscar.push_back(repetidos[repetidos.size() / 2]);
        }
    }

    // 2. Añadir casos estándar (si no son repetidos)
    valores_buscar.push_back(v.front());
    if (v.front() != v.back()) {
        valores_buscar.push_back(v.back());
    }
    valores_buscar.push_back(v[n / 2]);
    valores_buscar.push_back(v.back() + 100); // Valor que no existe

    // Eliminar duplicados en valores_buscar
    sort(valores_buscar.begin(), valores_buscar.end());
    valores_buscar.erase(unique(valores_buscar.begin(), valores_buscar.end()), valores_buscar.end());


    for (int x : valores_buscar) {
        // Reiniciar contadores
        OE_BN = 0;
        OE_BIN = 0;
        OE_INTER = 0;

        // Medir tiempo binario1
        auto start_bin1 = chrono::high_resolution_clock::now();
        BusquedaBinaria1(datos, 0, n - 1, x);
        auto end_bin1 = chrono::high_resolution_clock::now();
        double tiempo_bin1 = chrono::duration<double>(end_bin1 - start_bin1).count();

        // Medir tiempo binario2
        auto start_bin = chrono::high_resolution_clock::now();
        BusquedaBinaria2(datos, 0, n - 1, x);
        auto end_bin = chrono::high_resolution_clock::now();
        double tiempo_bin = chrono::duration<double>(end_bin - start_bin).count();

        // Medir tiempo interpolación
        auto start_inter = chrono::high_resolution_clock::now();
        BusquedaInterpolacion(datos, 0, n - 1, x);
        auto end_inter = chrono::high_resolution_clock::now();
        double tiempo_inter = chrono::duration<double>(end_inter - start_inter).count();

        // Escribir resultados
        archivo << n << ";" << distribucion << ";"
            <<OE_BN << ";" << OE_BIN << ";" << OE_INTER << ";"
            << fixed << setprecision(8) << tiempo_bin1 << ";" << tiempo_bin << ";" << tiempo_inter << "\n";

    }
}

int main() {
    const unsigned int semilla = 12345; // Una sola semilla
    ofstream archivo("resultados.csv");

    // Encabezados del CSV
    archivo << "Tamano;Distribucion;OE_Binaria1;OE_Binaria2;OE_Interpolacion;Tiempo_Binaria1(s);Tiempo_Binaria2(s);Tiempo_Interpolacion(s)\n";


    // Prueba específica para array con repeticiones controladas
    vector<int> testRepetidos = {
        1, 1, 1, 1, 1,  // Bloque grande al inicio
        2, 2,           // Bloque pequeño
        3,              // Valor único
        4, 4, 4, 4,      // Bloque medio
        5, 6, 7, 8, 9,  // Valores únicos
        10, 10, 10      // Bloque al final
    };
    realizarPruebas(testRepetidos, "repetidos-manual", archivo);

    // Pruebas con generación aleatoria de repeticiones
    vector<int> tamanosRepeticion = { 100, 1000, 10000 };

    for (int tam : tamanosRepeticion) {
        vector<int> v;
        generarVector(v, tam, "repetidos", semilla);
        realizarPruebas(v, "repetidos", archivo);
    }


    // Prueba específica para array vacío
    vector<int> vacio;
    realizarPruebas(vacio, "vacio", archivo);

    // Tamaños a probar
    vector<int> tamanos = { 1000, 2000, 3000, 4000, 5000, 10000, 20000, 30000, 40000, 50000 };
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