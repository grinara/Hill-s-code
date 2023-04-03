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
	cout << "������� ��� ����� ��� �������������: ";
	cin >> file_name_to_code;
	ifstream file1;
	file1.open(file_name_to_code.c_str(), ios::in | ios::binary);
	if (!file1.is_open()) { cout << "���� �� ������" << endl; return; }
	else if (file1.peek() == EOF){cout << "���� ����" << endl; return;}
	else { cout << "���� ������� ������" << endl; }
	string key;
	int k;
	int** mtr;
	int deter;
	while (true) {
		cout << "������� ����" << endl;
		cin >> key;
		k = matrix_size(key);// ���������� ������ �������
		mtr = create_mtr(k, key);// ������ �������-���� �� ������-�����
		deter = chek_det(mtr, k);// ������� ������������ �������
		if (deter == 0 || deter % 97 == 0) { cout << "������������ ����" << endl; }
		else { break; }
	}
	// �������� ������������ (  ���� �� ����� 0 ���  �������� ������� ������� � 97,
	// �� ��������, ����� ����� ������ ���� )
	mtr = invers(mtr, k);// ������ �������� ������� � ������� - �����
	bool fl = true;
	int str[100] = {0};
	int i = 0;
	char buff;
	int k1=0;
	while (fl) {//������� ���� - �� ������ �������� ����� �����������  k  �������� ������
		for (i = 0; fl && i < k; i++) { //��������� ������ ��������� �� �������������� ������:
			buff = file1.get();//��������� ������
			if (!file1.eof()) {
				str[i] = buff - 30; //���� ���� �� ���� ������� �����,��������������� �������
			}                         //��������� � ������
			else { fl = false; break; }
				
		}
		int k1 = i; 
		for (i = 0; i < k1; i++) { //���������  i ������� �������
			int S = 0;
			for (int j = 0; j < k; j++) {
				S = S + mtr[i][j] * str[j]; 
			}
			 S = (S % 97) + 30;// �������� ���� - ���  ��������� �������
			if (S == 30) { S = 13; cout << (char)S;  S = 10;// ���� ������� �� ������ ������
			}
			if (S == 31) { fl = false; break; }// ���� �������� ����� ����������
			cout << (char)S;// ����� ��������������� ������� �� �����
		}
	}
	cout << endl;
}