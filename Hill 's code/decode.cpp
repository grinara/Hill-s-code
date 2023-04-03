#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "Matrx.h"
using namespace std;
void decode() {
	
	string file_name_to_code;
	cout << "Введите имя файла для декодирования: ";
	cin >> file_name_to_code;
	ifstream file1;
	file1.open(file_name_to_code.c_str(), ios::in | ios::binary);
	if (!file1.is_open()) { cout << "Файл не открыт" << endl; return; }
	else if (file1.peek() == EOF){cout << "Файл пуст" << endl; return;}
	else { cout << "Файл успешно открыт" << endl; }
	string key;
	int k;
	int** mtr;
	int deter;
	while (true) {
		cout << "Введите ключ" << endl;
		cin >> key;
		k = matrix_size(key);// определяем размер матрицы
		mtr = create_mtr(k, key);// строим матрицу-ключ по строке-ключу
		deter = chek_det(mtr, k);// считаем определитель матрицы
		if (deter == 0 || deter % 97 == 0) { cout << "недопустимый ключ" << endl; }
		else { break; }
	}
	// проверка определителя (  если не равен 0 или  является взаимно простым с 97,
	// то подходит, иначе нужен другой ключ )
	mtr = invers(mtr, k);// строим обратную матрицу к матрице - ключу
	bool fl = true;
	int str[100] = {0};
	int i = 0;
	char buff;
	int k1=0;
	while (fl) {//внешний цикл - на каждой итерации будем дешифровать  k  символов текста
		for (i = 0; fl && i < k; i++) { //заполняем вектор символами из зашифрованного текста:
			buff = file1.get();//считываем символ
			if (!file1.eof()) {
				str[i] = buff - 30; //если файл не пуст находим число,соответствующее символу
			}                         //добавляем в вектор
			else { fl = false; break; }
				
		}
		int k1 = i; 
		for (i = 0; i < k1; i++) { //дешифруем  i элемент вектора
			int S = 0;
			for (int j = 0; j < k; j++) {
				S = S + mtr[i][j] * str[j]; 
			}
			 S = (S % 97) + 30;// получаем аски - код  исходного символа
			if (S == 30) { S = 13; cout << (char)S;  S = 10;// если переход на другую строку
			}
			if (S == 31) { fl = false; break; }// если исходный текст закончился
			cout << (char)S;// вывод расшифрованного символа на экран
		}
	}
	cout << endl;
}