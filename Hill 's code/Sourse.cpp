#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "Matrx.h"
using namespace std;
//Для текста и ключа можно использовать символы, аски-код которых лежит
//в пределах промежутка [32,127]. Каждому символу ставится в соответствие
//число равное аски-код минус 30. Переходу на следущую строку (подряд 
//стоящие аски-коды 10 и 13) соответствует число 0. Число 1 указывает окончание текста. 

void main() {
	setlocale(LC_ALL, "Russian");
	int check;
	cout << "Алфавит" << endl;
	for (int i = 32; i < 127; i++) { cout << char(i)<<" "; }
	cout << endl;
	while (true) {
		cout << "Для кодирования введите 0" << endl;
		cout << "Для разкодирования введите 1" << endl;
		cout << "Для выхода введите что угодно" << endl;
		scanf_s("%d", &check);
		if (check == 0) { coding(); }
		else if (check == 1) { decode(); }
		else { return; }
	}
}
