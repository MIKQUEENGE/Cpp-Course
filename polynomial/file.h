//file.h
#include "class_polynomial.h"
polynomial po[50];
void db_write() {
	fstream fout("DB.txt");
	fout.clear();
	fout<<sum<<endl;
	for (int i = 0; i < sum; i++) fout<<po[i];
	fout.close();
}
void db_read() {
	fstream fin("DB.txt");
	if(fin)fin>>sum;
	else sum=0;
	string s;
	for (int i = 0; i < sum; i++) {
		getline(fin,s);
		int k = po[i].input(s);
		if (k == 0) {
			cout<<"read file error! please restart!";
		}
		break;
	}
	fin.close();
}
