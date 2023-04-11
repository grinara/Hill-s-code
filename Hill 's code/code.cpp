#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <math.h>
#include "Header.h"
using namespace std;
void coding() {
	string file_name_to_code;
	cout << "Введите имя файла для кодирования: ";
	cin >> file_name_to_code;
	ifstream file1;
	file1.open(file_name_to_code.c_str(), ios::in | ios::binary);
	if (!file1.is_open()) { cout << "Файл не открыт" << endl; return; }
	else if (file1.peek() == EOF) { cout << "Файл пуст" << endl; return; }
	else { cout << "Файл успешно открыт" << endl; }
	string key;
	int k;
	int** mtr;
	int deter;
	while (true) {
		cout << "Введите ключ" << endl;
		cin >> key;
		k = matrix_size(key); // определяем размер матрицы
		mtr = create_mtr(k, key); // строим матрицу-ключ по строке-ключу
		deter = chek_det(mtr, k); // считаем определитель матрицы
		if (deter == 0 || deter % 97 == 0 || !cheak_key(key)) { cout << "недопустимый ключ" << endl; }
		else { break; }
	}
	// проверка определителя (  если не равен 0 и  является взаимно простым с 97,
	// то подходит, иначе нужен другой ключ )
	ofstream file_cip;
	file_cip.open("112.txt", ios::in | ios::trunc);
	bool fl = true;
	int str[100] = {0};
	int k1 = 0;
	int i = 0;
	char buff;
	cout << "Файл в зашифрованном виде" << endl;
	while (fl) { //внешний цикл - на каждой итерации будем шифровать  k  символов текста
		for (i = 0; i < k; i++) { str[i] = 1; }  // строим вектор размерности k из единиц
		for (i = 0; fl && i < k; i++) { // заполняем вектор символами из текста:
			buff = file1.get(); // считываем очередной символ
			if (file1.eof()) { fl = false; break; }// если файл не закончился
			if (buff > 126 || (buff < 32 && buff != 13 && buff != 10)) {//проверка на допустимость
				cout << "Файл содержит недопустимые символы" << endl;
				file1.close(); file_cip.close(); return;
			}
			if ((!file1.eof()) && (buff == 13)) { buff = file1.get(); buff = 30; } // если
			//  в тексте - переход на другую строку 
			if (!file1.eof()) { str[i] = buff-30;} // в вектор заносим число соотвествующее 
		}             //считанному символу ( аски-код   минус 30 )
		
		if (i !=0) { k1 = k; } 
		else { k1 = i; } 
		for (i = 0; i < k1; i++) { // кодируем i-элемент полученного вектора
			int S = 0;             
			for (int j = 0; j < k; j++) { 
				S = S + mtr[i][j] * str[j];
			} 
			S = (S % 97)+30; // получаем аски - код  шифрованного символа
			cout << (char)S; // выводим этот символ на экран
			file_cip.write((char*)&S, sizeof(char)); //записываем его  в  файл
		}
	}
	cout << endl;
	file1.close(); 
	file_cip.close();
}
