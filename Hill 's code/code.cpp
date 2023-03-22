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
	string key = "7tyuEFR";
	int k = matrix_size(key);
	int** mtr = create_mtr(k, key);
	int deter = chek_det(mtr, k);
	if (deter == 0|| deter % 97 == 0) return false;
	ifstream file1;
	ofstream file_cip;
	file1.open("11.txt", ios::out | ios::binary);
	file_cip.open("112.txt", ios::in | ios::binary);
	bool fl = true;
	//string str;
	int str[100] = {0};
	int k1 = 0;
	int i = 0;
	char buff;
	while (fl) {
		//str = "";
		for (i = 0; i < k; i++) { str[i] = 1; } //����� ������ ��� ����� �����������
		for (i = 0; fl && i < k; i++) { //������� ������ (������)
			buff = file1.get();
			if (!file1.eof()) { str[i] = buff-30;}
			else { fl = false;   break; }
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