#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
void next_route(int* r, int n) { // вычисл€ет следующий маршрут, использу€ алгоритм ƒейкстры
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
int chek_det(int** mtr, int n) {
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

int matrix_size(string str) { // размерность матрицы kXk
	int N = str.length();
	int k = sqrt(N);
	if (k * k != N) { k++; }
	return k;
}
int** create_mtr(int k,string str) { //матрица из ключа (дополнить по необходимости)
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
				mtr[i][j] = str[z]-30;
				z++;
			}
			cout << (int)mtr[i][j]<<" ";
		}
		cout << endl;
	}
	return mtr;
}
bool coding() {
	string key = "7asdR8aUYTREW88ff";
	int k = matrix_size(key);
	int** mtr = create_mtr(k, key);
	int deter = chek_det(mtr, k);
	if (deter == 0 || deter == 1 || deter % 97 == 0) return false;
	ifstream file1("11.txt", ios::out | ios::binary);
	ofstream file_cip("112.txt", ios::in | ios::binary);
	bool fl = true;
	list<int>da;
	string str;
	int i = 0;
	char buff;
	while (fl) {
		str = "";
		for (i = 0; i < k; i++)  str += 35; //чтобы вектор был одной размерности
		for (i = 0; fl && i < k; i++) { //находим строку (вектор)
			buff = file1.get();
			if (!file1.eof()) { str[i] = buff-30;}
			else { fl = false; break; }
		}
		int k1 = i;
		for (i = 0; i < k1; i++) { //кодирование через умножение вектора на матрицу
			int S = 0;
			for (int j = 0; j < k; j++) {
				S = S + mtr[i][j] * str[j];
			}
			S = S % 97+30;
			file_cip.write((char*)&S, sizeof(char));//записываем закодированный текст в файл
			da.push_back(S);
		}
	}
	list<int> ::iterator a;
	cout << endl;
	for (a = da.begin(); a != da.end(); a++) cout << (char)*a << " ";

}