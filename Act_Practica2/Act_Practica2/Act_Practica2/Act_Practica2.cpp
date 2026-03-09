#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// --- Merge y MergeSort (igual que antes) ---
void Merge(vector<int>& A, int izq, int medio, int der, vector<int>& Aux) {
    for (int i = izq; i <= der; i++) {
        Aux[i] = A[i];
    }
    int i = izq, j = medio + 1, k = izq;
    while (i <= medio && j <= der) {
        if (Aux[i] <= Aux[j]) {
            A[k++] = Aux[i++];
        }
        else {
            A[k++] = Aux[j++];
        }
    }
    while (i <= medio) {
        A[k++] = Aux[i++];
    }
}

void MergesortEstandar(vector<int>& A, int izq, int der, vector<int>& Aux) {
    if (izq < der) {
        int centro = (izq + der) / 2;
        MergesortEstandar(A, izq, centro, Aux);
        MergesortEstandar(A, centro + 1, der, Aux);
        Merge(A, izq, centro, der, Aux);
    }
}

// --- Nueva función para filtrar por repeticiones ---
vector<int> filtrarPorRepeticiones(vector<int>& A, int k) {
    vector<int> resultado;
    int n = A.size();
    if (n == 0) return resultado;

    int contador = 1; // Inicia en 1 porque al menos hay una ocurrencia
    for (int i = 1; i < n; i++) {
        if (A[i] == A[i - 1]) {
            contador++;
        }
        else {
            if (contador == k) {
                resultado.push_back(A[i - 1]);
            }
            contador = 1; // Reinicia el contador para el nuevo elemento
        }
    }
    // Verificar el último elemento del vector
    if (contador == k) {
        resultado.push_back(A.back());
    }
    return resultado;
}

// --- Algoritmo principal adaptado ---
void Mialgoritmo(vector<int>& T, int k) {
    int n = T.size();
    vector<int> Aux(n);

    // Paso 1: Ordenar con MergeSort
    MergesortEstandar(T, 0, n - 1, Aux);

    // Paso 2: Filtrar elementos que aparecen 'k' veces
    vector<int> elementos_k = filtrarPorRepeticiones(T, k);

    // Mostrar resultados
    cout << "Elementos que aparecen " << k << " veces (ordenados): ";
    for (int num : elementos_k) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    // Ejemplo 1: k = 2
    vector<int> A = { 4, 2, 2, 8, 5, 1, 2, 4 };
    cout << "Vector original: ";
    for (int num : A) cout << num << " ";
    cout << endl;

    Mialgoritmo(A, 2); // Salida esperada: 4 (aparece 2 veces)

    // Ejemplo 2: k = 1 (elementos únicos)
    vector<int> B = { 3, 1, 2, 3, 3, 4, 4 };
    cout << "Vector original: ";
    for (int num : B) cout << num << " ";
    cout << endl;

    Mialgoritmo(B, 1); // Salida esperada: 1 2

    // Ejemplo 3: k = 3
    vector<int> C = { 1, 1, 1, 2, 2, 3, 3, 3, 3 };
    cout << "Vector original: ";
    for (int num : C) cout << num << " ";
    cout << endl;

    Mialgoritmo(C, 3); // Salida esperada: 1

    return 0;
}