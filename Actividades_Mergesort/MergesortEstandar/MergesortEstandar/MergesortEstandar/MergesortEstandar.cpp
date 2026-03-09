// MergesortEstandar.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>

using namespace std;

template <typename elem>

void Merge(vector<elem>& T, int e, int m,int d)
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

void MergesortEstandar(vector<elem>& A, int izq, int der)
{
	if (izq < der)
	{
		int centro = (izq + der) / 2;
		MergesortEstandar(A, izq, centro);
		MergesortEstandar(A, centro + 1, der);
		Merge(A, izq, centro, der);
	}
}


int main()
{
	vector<int> arr = {3, 7, 9, 2, 5, 8 };
	cout << "Array original: ";
	for (int num : arr) cout << num << " ";
	cout << endl;

	MergesortEstandar(arr, 0, arr.size() - 1);

	cout << "Array ordenado: ";
	for (int num : arr) cout << num << " ";
	cout << endl;


	return 0;
};

