// MergesortEstandar.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
using namespace std::chrono;

//implementacion mergesort estandar, crea subarrays temporales
template <typename elem>
void Merge1(vector<elem>& T, int e, int m, int d)
{
	vector<elem> B(d - e + 1); //B es un array auxiliar para la mezcla
	int i = e;
	int j = m + 1;
	int k = 0;
	while (i <= m && j <= d)
	{
		if (T[i] < T[j])
		{
			B[k] = T[i];
			i++;
		}
		else
		{
			B[k] = T[j];
			j++;
		}
		k++;
	}
	while (i <= m)
	{
		B[k] = T[i];
		i++;
		k++;
	}
	while (j <= d)
	{
		B[k] = T[j];
		j++;
		k++;
	}
	for (int i = 0; i < k; i++)
	{
		T[e + i] = B[i];
	}
}


template <typename elem>
void MergesortEstandar1(vector<elem>& A, int izq, int der)
{
	if (izq < der)
	{
		int centro = (izq + der) / 2;
		MergesortEstandar1(A, izq, centro);
		MergesortEstandar1(A, centro + 1, der);
		Merge1(A, izq, centro, der);
	}
}

//implementacion mergesort modificado, no crea subarrays temporales
// Implementación mergesort modificado (usa un solo array temporal)
template <typename elem>
void Merge2(vector<elem>& A, int izq, int medio, int der, vector<elem>& Aux) {
	// Copiar el segmento actual al array auxiliar
	for (int i = izq; i <= der; i++) {
		Aux[i] = A[i];
	}

	int i = izq;       // Índice para la mitad izquierda (Aux[izq..medio])
	int j = medio + 1; // Índice para la mitad derecha (Aux[medio+1..der])
	int k = izq;       // Índice para el array original (A[izq..der])

	// Mezclar desde Aux[] hacia A[]
	while (i <= medio && j <= der) {
		if (Aux[i] <= Aux[j]) {
			A[k++] = Aux[i++];
		}
		else {
			A[k++] = Aux[j++];
		}
	}

	// Copiar los elementos restantes de la izquierda (si hay)
	while (i <= medio) {
		A[k++] = Aux[i++];
	}
}

template <typename elem>
void MergesortEstandar2(vector<elem>& A, int izq, int der, vector<elem>& Aux) {
	if (izq < der) {
		int centro = (izq + der) / 2;
		MergesortEstandar2(A, izq, centro, Aux);
		MergesortEstandar2(A, centro + 1, der, Aux);
		Merge2(A, izq, centro, der, Aux);
	}
}

vector<int> generarArrayAleatorio(int tamano) {
	vector<int> arr(tamano);
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(1, 10000);

	for (int i = 0; i < tamano; i++) {
		arr[i] = distrib(gen);
	}
	return arr;
}

void experimento() {
	vector<int> tamanos = {10,50, 100,500, 1000, 2500, 5000, 7500, 10000, 12500, 15000, 17500, 100000 };
	int repeticiones = 5;

	cout << "Comparación de MergeSort estándar vs. optimizado\n";
	cout << "------------------------------------------------\n";

	for (int tamano : tamanos) {
		double tiempo_total_estandar = 0;
		double tiempo_total_optimizado = 0;

		cout << "\nTamaño del array: " << tamano << endl;

		for (int i = 0; i < repeticiones; i++) {
			vector<int> arr = generarArrayAleatorio(tamano);
			vector<int> arr_copia1 = arr;  // Para MergeSort estándar
			vector<int> arr_copia2 = arr;  // Para MergeSort optimizado
			vector<int> aux(tamano);       // Array auxiliar para la versión optimizada

			// Medir MergeSort estándar
			auto inicio1 = high_resolution_clock::now();
			MergesortEstandar1(arr_copia1, 0, arr_copia1.size() - 1);
			auto fin1 = high_resolution_clock::now();
			tiempo_total_estandar += duration_cast<milliseconds>(fin1 - inicio1).count();

			// Medir MergeSort optimizado
			auto inicio2 = high_resolution_clock::now();
			MergesortEstandar2(arr_copia2, 0, arr_copia2.size() - 1, aux);
			auto fin2 = high_resolution_clock::now();
			tiempo_total_optimizado += duration_cast<milliseconds>(fin2 - inicio2).count();
		}

		double tiempo_promedio_estandar = tiempo_total_estandar / repeticiones;
		double tiempo_promedio_optimizado = tiempo_total_optimizado / repeticiones;

		cout << "MergeSort estándar: " << tiempo_promedio_estandar << " ms\n";
		cout << "MergeSort optimizado: " << tiempo_promedio_optimizado << " ms\n";
		cout << "Diferencia: " << (tiempo_promedio_estandar - tiempo_promedio_optimizado) << " ms\n";
	}
}

int main()
{
	experimento();

	return 0;
};

