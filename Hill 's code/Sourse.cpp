#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "Matrx.h"
using namespace std;
//��� ������ � ����� ����� ������������ �������, ����-��� ������� �����
//� �������� ���������� [32,127]. ������� ������� �������� � ������������
//����� ������ ����-��� ����� 30. �������� �� �������� ������ (������ 
//������� ����-���� 10 � 13) ������������� ����� 0. ����� 1 ��������� ��������� ������. 

void main() {
	setlocale(LC_ALL, "Russian");
	int check;
	cout << "�������" << endl;
	for (int i = 32; i < 127; i++) { cout << char(i)<<" "; }
	cout << endl;
	while (true) {
		cout << "��� ����������� ������� 0" << endl;
		cout << "��� �������������� ������� 1" << endl;
		cout << "��� ������ ������� ��� ������" << endl;
		scanf_s("%d", &check);
		if (check == 0) { coding(); }
		else if (check == 1) { decode(); }
		else { return; }
	}
}
