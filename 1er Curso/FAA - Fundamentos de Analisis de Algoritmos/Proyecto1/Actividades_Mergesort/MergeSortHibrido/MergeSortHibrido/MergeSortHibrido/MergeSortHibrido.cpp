// MergeSortHibrido.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
using namespace std::chrono;

//Funcion insertionSort, con la cual insertamos los elementos ya ordenados en el vector
template <typename elem>
void InsertionSort(vector<elem>& T, int e, int d)
{
	for (int i = e + 1; i <= d; i++)
	{
		elem x = T[i];
		int j = i - 1;
		while (j >= e && T[j] > x)
		{
			T[j + 1] = T[j];
			j--;
		}
		T[j + 1] = x;
	}
}


//funcion que mezcla los dos vectores pasados a la funcion MergeSort
template <typename elem>
void Merge(vector<elem>& T, int e, int m, int d)
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
void MergesortHibrido(vector<elem>& A, int izq, int der, int k)
{
	if ((der - izq + 1) <= k)
	{
		InsertionSort(A, izq, der);
	}
	else if (izq < der)// Si el vector tiene más de k elementos, se divide en dos mitades y se ordena cada mitad
	{
		int centro = (izq + der) / 2;
		MergesortHibrido(A, izq, centro,k);
		MergesortHibrido(A, centro + 1, der,k);
		Merge(A, izq, centro, der);
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
	vector<int> tamanos = { 100, 1000, 10000, 100000 };
	vector<int> k_values = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 };
	int repeticiones = 5;

	for (int tamano : tamanos) {
		cout << "\nTamaño del array: " << tamano << endl;
		cout << "k\tTiempo promedio (ms)\n";

		for (int k : k_values) {
			double tiempo_total = 0;

			for (int i = 0; i < repeticiones; i++) {
				vector<int> arr = generarArrayAleatorio(tamano);
				vector<int> arr_copia = arr;

				auto inicio = high_resolution_clock::now();
				MergesortHibrido(arr_copia, 0, arr_copia.size() - 1, k);
				auto fin = high_resolution_clock::now();

				tiempo_total += duration_cast<milliseconds>(fin - inicio).count();
			}

			double tiempo_promedio = tiempo_total / repeticiones;
			cout << k << "\t" << tiempo_promedio << endl;
		}
	}
}

int main()
{
	experimento();
	return 0;
}

