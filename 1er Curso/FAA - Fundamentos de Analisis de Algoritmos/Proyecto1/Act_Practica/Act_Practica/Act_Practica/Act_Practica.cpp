#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Función Merge modificada para tu implementación
void Merge(vector<int>& A, int izq, int medio, int der, vector<int>& Aux) {
    // Copiar el segmento a Aux
    for (int i = izq; i <= der; i++) {
        Aux[i] = A[i];
    }

    int i = izq;      // Índice para la mitad izquierda
    int j = medio + 1; // Índice para la mitad derecha
    int k = izq;       // Índice para el array original

    // Mezclar las dos mitades ordenadas
    while (i <= medio && j <= der) {
        if (Aux[i] <= Aux[j]) {
            A[k++] = Aux[i++];
        }
        else {
            A[k++] = Aux[j++];
        }
    }

    // Copiar elementos restantes de la izquierda (si los hay)
    while (i <= medio) {
        A[k++] = Aux[i++];
    }
}

// MergeSort (tu versión)
void MergesortEstandar(vector<int>& A, int izq, int der, vector<int>& Aux) {
    if (izq < der) {
        int centro = (izq + der) / 2;
        MergesortEstandar(A, izq, centro, Aux);
        MergesortEstandar(A, centro + 1, der, Aux);
        Merge(A, izq, centro, der, Aux);
    }
}

// Función para filtrar elementos únicos
vector<int> filtrarUnicos(vector<int>& A) {
    vector<int> unicos;
    int n = A.size();
    if (n == 0) return unicos;

    for (int i = 0; i < n; i++) {
        bool esUnico = true;
        // Comparar con el anterior y el siguiente
        if (i > 0 && A[i] == A[i - 1]) esUnico = false;
        if (i < n - 1 && A[i] == A[i + 1]) esUnico = false;

        if (esUnico) {
            unicos.push_back(A[i]);
        }
    }
    return unicos;
}

// Algoritmo principal (adaptado a tu estructura)
void Mialgoritmo(vector<int>& T) {
    int n = T.size();
    vector<int> Aux(n); // Vector auxiliar para MergeSort

    // Paso 1: Ordenar con MergeSort
    MergesortEstandar(T, 0, n - 1, Aux);

    // Paso 2: Filtrar elementos únicos
    vector<int> unicos = filtrarUnicos(T);

    // Mostrar resultados
    cout << "Elementos únicos ordenados: ";
    for (int num : unicos) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    // Ejemplo 1
    vector<int> A = { 4, 2, 2, 8, 5, 1, 2, 4 };
    cout << "Vector original: ";
    for (int num : A) cout << num << " ";
    cout << endl;

    Mialgoritmo(A); // Salida esperada: 1 5 8

    // Ejemplo 2 (todos únicos)
    vector<int> B = { 3, 1, 2 };
    cout << "Vector original: ";
    for (int num : B) cout << num << " ";
    cout << endl;

    Mialgoritmo(B); // Salida esperada: 1 2 3

	vector<int> C = { 1, 1, 3, 4, 3 };
	cout << "Vector original: ";
	for (int num : C) cout << num << " ";
	cout << endl;
	Mialgoritmo(C); // Salida esperada: 4

    return 0;
}