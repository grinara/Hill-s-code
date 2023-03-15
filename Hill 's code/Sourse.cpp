#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "Header.h"
using namespace std;
void main() {
	setlocale(LC_ALL, "Russian");
	ifstream file1("11.txt", ios::out | ios::binary);
	char buff;
	while(!file1.eof()){
		buff = file1.get();
		if (buff>127) { cout << "Файл содержит недопустимые символы" << endl; file1.close(); return; }
	}
	if (!coding()) cout << "недопустимый ключ" << endl;
}
