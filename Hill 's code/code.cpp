#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <math.h>
#include "Matrx.h"
using namespace std;
bool coding() {
	cout << "������� ����" << endl;
	string key;
	cin >> key;
	string file_name_to_code;
	cout << "������� ��� ����� ��� �����������: ";
	cin >> file_name_to_code;
	ifstream file1;
	file1.open(file_name_to_code.c_str(), ios::in | ios::binary);
	if (file1) { cout << "���� ������� ������" << endl; }
	else { cout << "���� �� ������" << endl; return false; }

	int k = matrix_size(key);
	int** mtr = create_mtr(k, key);
	int deter = chek_det(mtr, k);
	if (deter == 0 || deter % 97 == 0) { cout << "������������ ����" << endl; return false; }
	ofstream file_cip;
	file_cip.open("112.txt", ios::in | ios::trunc);
	bool fl = true;
	int str[100] = {0};
	int k1 = 0;
	int i = 0;
	char buff;
	cout << "���� � ������������� ����" << endl;
	while (fl) {
		for (i = 0; i < k; i++) { str[i] = 1; } //����� ������ ��� ����� �����������
		for (i = 0; fl && i < k; i++) { //������� ������ (������)
			buff = file1.get();
			if (file1.eof()) { fl = false; break; }
			if (buff > 126 || (buff < 32 && buff != 13 && buff != 10)) { cout << "���� �������� ������������ �������"<<endl; file1.close(); return false; }
			if ((!file1.eof()) && (buff == 13)) { buff = file1.get(); buff = 30; }
			if (!file1.eof()) { str[i] = buff-30;}
		}
		
		if (i !=0) { k1 = k; }
		else { k1 = i; }
		for (i = 0; i < k1; i++) { //����������� ����� ��������� ������� �� �������
			int S = 0;
			for (int j = 0; j < k; j++) {
				S = S + mtr[i][j] * str[j];
			}
			S = (S % 97)+30;
			//cout  << S;
			cout << (char)S;
			file_cip.write((char*)&S, sizeof(char));//���������� �������������� ����� � ����
		}
	}
	file1.close(); 
	file_cip.close();
}