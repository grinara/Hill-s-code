#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
using namespace std;
void coding();
void decode();
inline bool cheak_key(string key) {
	for (int i = 0; i < key.size(); i++) {
		if (key[i] < 32 || key[i]>127) { return false; }
	}
	return true;
}
//****НАХОДИМ ЧИСЛО a ПО МОДУЛЮ b
inline int mod(int a, int b) {
	if (a < 0) return a % b + b;
	return a % b;
}
//**** ОПРЕДЕЛЯЕМ ПЕРЕСТАНОВКУ ПО АЛГОРИТМУ ДЕЙКСТРЫ
inline void next_route(int* r, int n) { 
	int i = n - 1;//начинаем с конца исходной перестановки
	int j = n - 1;
	while (r[i - 1] > r[i]) { //двигаемся влево, ищем элемент нарушающий убывание
		i--;
	}                          //начинаем с конца исходной перестановки
	while (r[j] < r[i - 1]) { //ищем элемент больше чем найденный 
		j--;
	}
	int x = r[i - 1]; // меняем их местами
	r[i - 1] = r[j];
	r[j] = x;
	for (int k = i, m = n - 1; k < m; k++, m--) {
		int c = r[k];//инвертируем "хвост"
		r[k] = r[m];
		r[m] = c;
	}
}
//**** ВЫЧИСЛЯЕМ ОПРЕДЕЛИТЕЛЬ МАТРИЦЫ МЕТОДОМ ПЕРЕСТАНОВОК
//т.е. как сумму n! слагаемых, каждое из которых есть произведение
// n элементов матрицы, взятое с определённым знаком
inline int chek_det(int** mtr, int n) {
	int nf = 1;
	int* r = new int[n];
	for (int i = 0; i < n; i++) { r[i] = i; }//начальная перестановка
	int P = 1, S = 0, f = 0;
	for (int i = 1; i <= n; i++) {//считаем n!(количество перестановок)
		nf = nf * i;
	}
	for (int i = 0; i < nf; i++) {//каждая итерация цикла - очередная перестановка
		for (int x = 0; x < n; x++) {//количество инверсий в перестановке
			for (int y = x + 1; y < n; y++) {//т.е. число пар в которых
				if (r[x] > r[y]) { f++; };//левое число больше правого
			}
		}
		for (int j = 0; j < n; j++) {//находим произведение элементов, 
			P = mtr[j][r[j]] * P;//соответствующих данной перестановки
		}//номер строки-позиция числа, номер столбца-само число
		next_route(r, n);// следущая перестановка
		if (f % 2 != 0) { P = -P; };// определяем знак произведения 
		//если число инверсий - нечётное, то знак меняем на противоположный
		S = P + S;
		P = 1;
		f = 0;
	}

	return S;
}
//**** НАХОДИМ РАЗМЕРНОСТЬ МАТРИЦЫ-КЛЮЧА
inline int matrix_size(string str) { 
	int N = str.length();
	int k = sqrt(N);// находим целую часть корня от количества элементов
	if (k * k != N) { k++; }//если количество элементов не равно квадрату
	//то  k берём на единицу больше
	if (k == 1) { k = 2; }  //если в ключе всего один символ, матрица для 
	return k;               //него будет 2 на 2
}
//**** СТРОИМ МАТРИЦУ-КЛЮЧ ИЗ СТРОКИ-КЛЮЧА
inline int** create_mtr(int k, string str) { 
	int** mtr = new int* [k];
	int z = 0;
	for (int i = 0; i < k; i++) {
		mtr[i] = new int[k];
		for (int j = 0; j < k; j++) {//заполняем созданную матрицу
			mtr[i][j] = 35;     // символом "*" 
		}//таким образом если количество символов
	}//в ключе меньше чем k в квадрате, то оставшиеся будут = 35
	for (int i = 0; i < k; i++) {   //заполняем матрицу числами,соответствующими 
		for (int j = 0; j < k; j++) {//символам строки-ключа
			if (z != str.length()) {  
				mtr[i][j] = str[z] - 30;
				z++;
			}
		}
	}
	return mtr;
}
//**** СТРОИМ МИНОР ДЛЯ ЭЛЕМЕНТА (o-НОМЕР СТРОКИ,p-НОМЕР СТОЛБЦА)
inline int** minor_seach(int** mtr, long long n, long long o, long long p) {
	int* minor = new int[n * n - 2*n + 1];  //создаём вектор размерности
	int** minor_mtr = new int* [n];      // (n-1) в квадрате
	for (int i = 0; i < n; i++) { minor_mtr[i] = new int[n]; }
	int z = 0;
	for (int i = 0; i < n; i++) {  //заносим в вектор последовательно
		for (int j = 0; j < n; j++) {  // элементы матрицы кроме элементов,у которых
			if (i != o && j != p) { minor[z] = mtr[i][j]; z++; }
		}  // номер строки=o  или номер столбца=p
	}
	z = 0;
	for (int i = 0; i < n-1; i++) {  //формируем из вектора матрицу размерности
		for (int j = 0; j < n-1; j++) {  //(n-1) на (n-1)
			minor_mtr[i][j] = minor[z];
			z++;
		}
	}
	return minor_mtr;
}
//**** ТРАНСПОНИРУЕМ МАТРИЦУ
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
//**** СТРОИМ ОБРАТНУЮ МАТРИЦУ РАЗМЕРНОСТИ n на n ПО МОДУЛЮ 97
inline int** invers(int** mtr, int n) {
	int** mtr_inv = new int* [n];
	for (int i = 0; i < n; i++) { mtr_inv[i] = new int[n]; }

	int S = chek_det(mtr, n); // S - определитель матрицы ключа
	S = mod(S, 97);
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
			//берём определитель по mod 97
			mtr_inv[i][j] = mod(mtr_inv[i][j] * x, 97); // умножаем на обратный элемент
			// определителя, берём по mod 97

		}

	}
	mtr_inv = trans(mtr_inv, n);   //транспонируем матрицу
	return mtr_inv;
}
