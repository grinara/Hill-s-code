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
//****������� ����� a �� ������ b
inline int mod(int a, int b) {
	if (a < 0) return a % b + b;
	return a % b;
}
//**** ���������� ������������ �� ��������� ��������
inline void next_route(int* r, int n) { 
	int i = n - 1;//�������� � ����� �������� ������������
	int j = n - 1;
	while (r[i - 1] > r[i]) { //��������� �����, ���� ������� ���������� ��������
		i--;
	}                          //�������� � ����� �������� ������������
	while (r[j] < r[i - 1]) { //���� ������� ������ ��� ��������� 
		j--;
	}
	int x = r[i - 1]; // ������ �� �������
	r[i - 1] = r[j];
	r[j] = x;
	for (int k = i, m = n - 1; k < m; k++, m--) {
		int c = r[k];//����������� "�����"
		r[k] = r[m];
		r[m] = c;
	}
}
//**** ��������� ������������ ������� ������� ������������
//�.�. ��� ����� n! ���������, ������ �� ������� ���� ������������
// n ��������� �������, ������ � ����������� ������
inline int chek_det(int** mtr, int n) {
	int nf = 1;
	int* r = new int[n];
	for (int i = 0; i < n; i++) { r[i] = i; }//��������� ������������
	int P = 1, S = 0, f = 0;
	for (int i = 1; i <= n; i++) {//������� n!(���������� ������������)
		nf = nf * i;
	}
	for (int i = 0; i < nf; i++) {//������ �������� ����� - ��������� ������������
		for (int x = 0; x < n; x++) {//���������� �������� � ������������
			for (int y = x + 1; y < n; y++) {//�.�. ����� ��� � �������
				if (r[x] > r[y]) { f++; };//����� ����� ������ �������
			}
		}
		for (int j = 0; j < n; j++) {//������� ������������ ���������, 
			P = mtr[j][r[j]] * P;//��������������� ������ ������������
		}//����� ������-������� �����, ����� �������-���� �����
		next_route(r, n);// �������� ������������
		if (f % 2 != 0) { P = -P; };// ���������� ���� ������������ 
		//���� ����� �������� - ��������, �� ���� ������ �� ���������������
		S = P + S;
		P = 1;
		f = 0;
	}

	return S;
}
//**** ������� ����������� �������-�����
inline int matrix_size(string str) { 
	int N = str.length();
	int k = sqrt(N);// ������� ����� ����� ����� �� ���������� ���������
	if (k * k != N) { k++; }//���� ���������� ��������� �� ����� ��������
	//��  k ���� �� ������� ������
	if (k == 1) { k = 2; }  //���� � ����� ����� ���� ������, ������� ��� 
	return k;               //���� ����� 2 �� 2
}
//**** ������ �������-���� �� ������-�����
inline int** create_mtr(int k, string str) { 
	int** mtr = new int* [k];
	int z = 0;
	for (int i = 0; i < k; i++) {
		mtr[i] = new int[k];
		for (int j = 0; j < k; j++) {//��������� ��������� �������
			mtr[i][j] = 35;     // �������� "*" 
		}//����� ������� ���� ���������� ��������
	}//� ����� ������ ��� k � ��������, �� ���������� ����� = 35
	for (int i = 0; i < k; i++) {   //��������� ������� �������,���������������� 
		for (int j = 0; j < k; j++) {//�������� ������-�����
			if (z != str.length()) {  
				mtr[i][j] = str[z] - 30;
				z++;
			}
		}
	}
	return mtr;
}
//**** ������ ����� ��� �������� (o-����� ������,p-����� �������)
inline int** minor_seach(int** mtr, int n, int o, int p) {
	int* minor = new int[n * n - 2*n + 1];  //������ ������ �����������
	int** minor_mtr = new int* [n];      // (n-1) � ��������
	for (int i = 0; i < n; i++) { minor_mtr[i] = new int[n]; }
	int z = 0;
	for (int i = 0; i < n; i++) {  //������� � ������ ���������������
		for (int j = 0; j < n; j++) {  // �������� ������� ����� ���������,� �������
			if (i != o && j != p) { minor[z] = mtr[i][j]; z++; }
		}  // ����� ������=o  ��� ����� �������=p
	}
	z = 0;
	for (int i = 0; i < n-1; i++) {  //��������� �� ������� ������� �����������
		for (int j = 0; j < n-1; j++) {  //(n-1) �� (n-1)
			minor_mtr[i][j] = minor[z];
			z++;
		}
	}
	return minor_mtr;
}
//**** ������������� �������
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
//**** ������ �������� ������� ����������� n �� n �� ������ 97
inline int** invers(int** mtr, int n) {
	int** mtr_inv = new int* [n];
	for (int i = 0; i < n; i++) { mtr_inv[i] = new int[n]; }

	int S = chek_det(mtr, n); // S - ������������ ������� �����
	S = mod(S, 97);
	// ���� �������� ������� x � ������������ S �� ������ 97. 
	// (������ ����������  ����������� �������� �������). ��� ��� S � 97 
	// ������� ������� , ��  x  ����������� ���������� 
	// � �������� ������ ���������  S*x=1 (mod 97). ����� 
	// ������������  ������� ���������  ��������� �������.
	int x = 0, y = 0;
	while (y != 1) {
		x = x + 1;
		y = (S * x) % 97;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {   //��� ������� �������� �������
			int** min = minor_seach(mtr, n, i, j); // ������  �����
			int det = chek_det(min, n - 1);// ������� ������������ ������
			mtr_inv[i][j] = mod(pow(-1, i + j) * det, 97);// ���������� ���� 
			//���� ������������ �� mod 97
			mtr_inv[i][j] = mod(mtr_inv[i][j] * x, 97); // �������� �� �������� �������
			// ������������, ���� �� mod 97

		}

	}
	mtr_inv = trans(mtr_inv, n);   //������������� �������
	return mtr_inv;
}