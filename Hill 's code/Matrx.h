#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
using namespace std;
inline int mod(int a, int b) {
	if (a < 0) return a % b + b;
	return a % b;
}
inline void next_route(int* r, int n) { // вычисляет следующий маршрут, используя алгоритм Дейкстры
	int i = n - 1;
	int j = n - 1;
	while (r[i - 1] > r[i]) { // поиск элемент нарушающего последовательность по убыванию
		i--;
	}
	while (r[j] < r[i - 1]) { //ищем элемент больше чем r[i-1]
		j--;
	}
	int x = r[i - 1]; // обмениваем их местами
	r[i - 1] = r[j];
	r[j] = x;
	for (int k = i, m = n - 1; k < m; k++, m--) {
		int c = r[k];
		r[k] = r[m];
		r[m] = c;
	}
}
inline int chek_det(int** mtr, int n) {
	int nf = 1;
	int* r = new int[n];
	for (int i = 0; i < n; i++) { r[i] = i; }
	int P = 1, S = 0, f = 0;
	for (int i = 1; i <= n; i++) {
		nf = nf * i;
	}
	for (int i = 0; i < nf; i++) {
		for (int x = 0; x < n; x++) {
			for (int y = x + 1; y < n; y++) {
				if (r[x] > r[y]) { f++; };
			}
		}
		for (int j = 0; j < n; j++) {
			P = mtr[j][r[j]] * P;
		}
		next_route(r, n);
		if (f % 2 != 0) { P = -P; };
		S = P + S;
		P = 1;
		f = 0;
	}

	return S;
}

inline int matrix_size(string str) { // размерность матрицы kXk
	int N = str.length();
	int k = sqrt(N);
	if (k * k != N) { k++; }
	if (k == 1) { k = 2; }
	return k;
}
inline int** create_mtr(int k, string str) { //матрица из ключа (дополнить по необходимости)
	int** mtr = new int* [k];
	int z = 0;
	for (int i = 0; i < k; i++) {
		mtr[i] = new int[k];
		for (int j = 0; j < k; j++) {
			mtr[i][j] = 35;
		}
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (z != str.length()) {
				mtr[i][j] = str[z] - 30;
				z++;
			}
			//cout << (int)mtr[i][j] << " ";
		}
		cout << endl;
	}
	return mtr;
}
inline int** minor_seach(int** mtr, int n, int o, int p) {
	int* minor = new int[n * n - n];
	int** minor_mtr = new int* [n];
	for (int i = 0; i < n; i++) { minor_mtr[i] = new int[n]; }
	int z = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != o && j != p) { minor[z] = mtr[i][j]; z++; }
		}
	}
	//cout << endl;
	z = 0;
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n-1; j++) {
			minor_mtr[i][j] = minor[z];
			//cout << minor_mtr[i][j] << " ";
			z++;
		}
		//cout << endl;
	}
	return minor_mtr;
}
inline int** trans(int** mtr, int n) {
	int** mtr_copy = new int* [n];
	for (int i = 0; i < n; i++) {
		mtr_copy[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mtr_copy[j][i] = mtr[i][j];
		}
	}

	return mtr_copy;
}
inline int** invers(int** mtr, int n) {
	int** mtr_inv = new int* [n];
	for (int i = 0; i < n; i++) { mtr_inv[i] = new int[n]; }

	int S = chek_det(mtr, n); // S - определитель матрицы ключа
	//cout << "S - " << S << endl;
	S = mod(S, 97);
	//cout << "S - " << S << endl;

	// Ищем обратный элемент x к определителю S по модулю 97. 
	// (обычно используют  расширенный алгоритм Евклида). Так как S и 97 
	// взаимно простые , то  x  обязательно существует 
	// и является корнем уравнения  S*x=1 (mod 97). Можно 
	// ограничиться  простым перебором  возможных решений.
	int x = 0, y = 0;
	while (y != 1) {
		x = x + 1;
		y = (S * x) % 97;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {   //для каждого элемента матрицы
			int** min = minor_seach(mtr, n, i, j); // строим  минор
			int det = chek_det(min, n - 1);// считаем определитель минора
			mtr_inv[i][j] = mod(pow(-1, i + j) * det, 97);// определяем знак 
			//берём по mod 97
			mtr_inv[i][j] = mod(mtr_inv[i][j] * x, 97); // умножаем на обратный элемент
			// определителя, берём по mod 97

		}

	}
	mtr_inv = trans(mtr_inv, n);   //транспонируем матрицу
	//cout << "x - " << x << endl;
	for (int i = 0; i < n; i++) {// выводим обратную матрицу
		for (int j = 0; j < n; j++) {
			//cout << mtr_inv[i][j] << " ";
		}
		//cout << endl;
	}
	return mtr_inv;
}