#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "Matrx.h"
using namespace std;
bool decode() {
	cout << "¬ведите ключ" << endl;
	string key;
	cin >> key;
	string file_name_to_code;
	cout << "¬ведите им€ файла дл€ кодировани€: ";
	cin >> file_name_to_code;
	ifstream file1;
	file1.open(file_name_to_code.c_str(), ios::in | ios::binary);
	if (file1) { cout << "‘айл успешно открыт" << endl; }
	else { cout << "‘айл не открыт" << endl; return false; }
	int k = matrix_size(key);
	int** mtr = create_mtr(k, key);
	int deter = chek_det(mtr, k);
	mtr = invers(mtr, k);
	if (deter == 0 || deter % 97 == 0) { cout << "недопустимый ключ" << endl; return false; }
	bool fl = true;
	int str[100] = {0};
	int i = 0;
	char buff;
	int k1=0;
	int k2 = 0;
	while (fl) {
		for (i = 0; i < k; i++) { str[i] = 1; } //чтобы вектор был одной размерности
		for (i = 0; fl && i < k; i++) { //находим строку (вектор)
			buff = file1.get();
			if (!file1.eof()) {
				str[i] = buff - 30; 
			}
			else { fl = false; break; }
				
		}
		
		int k1 = i;
		for (i = 0; i < k1; i++) { //декодирование через умножение вектора на матрицу
			int S = 0;
			for (int j = 0; j < k; j++) {
				S = S + mtr[i][j] * str[j];
			}
			S = (S % 97) + 30;
			if (S == 30) { S = 13; cout << (char)S;  S = 10;
			}
			if (S == 31) { fl = false; break; }
			cout << (char)S;
		}
	}
}