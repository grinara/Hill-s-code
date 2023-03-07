#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
using namespace std;
int is_the_square(string str) {
	int N = str.length();
	int k = sqrt(N);
	while ((k + 1) * (k - 1) < (N - 1)) {
		k++;
	}
	return k;
}
int** create_mtr(int k,string str) {
	int** mtr = new int* [k];
	int z = 0;
	for (int i = 0; i < k; i++) {
		mtr[i] = new int[k];
		for (int j = 0; j < k; j++) {
			mtr[i][j] = 65;
		}
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (z != str.length()) {
				mtr[i][j] = str[z];
				z++;
			}
			cout << (int)mtr[i][j]<<" ";
		}
		cout << endl;
	}
	return mtr;
}
void coding(int k,int** mtr) {
	ifstream file1("11.txt", ios::out | ios::binary);
	ofstream file_cip("112.txt", ios::in | ios::binary);
	bool fl = true;
	list<int>da;
	string str;
	int i = 0;
	char buff;
	while (fl) {
		str = "";
		
		for (i = 0; i < k; i++)  str += "A"; 

		for (i = 0; fl && i < k; i++) {
			buff = file1.get();
			if (!file1.eof()) { str[i] = buff; cout << (int)str[i]<<" "; }
			else { fl = false; break; }
		}
		int k1 = i;
		
		for (i = 0; i < k1; i++) {
			int S = 0;
			for (int j = 0; j < k; j++) {
				S = S + mtr[i][j] * str[j];
			}
			S = S % 97;
			file_cip.write((char*)&S, sizeof(int));
			//da.push_back(S);
		}
	}
	//list<int> ::iterator a;
	//cout << endl;
	//for (a = da.begin(); a != da.end(); a++) cout << *a << " ";
}
void main() {
	string ss = "asdfa";
	int k = is_the_square(ss);
	int** mtr = create_mtr(k, ss);
	coding(k, mtr);

}