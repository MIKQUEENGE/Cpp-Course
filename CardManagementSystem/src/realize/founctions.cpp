/*
 the founctions following is easy to realize
 so there is no note
 */



#include "../../include/founctions.h"

bool isNumber(string s) {
	if (s.length()>0) {
		if (s.length() == 1&& s[0] == '0') return true;
		if (s[0]=='-'||(s[0]>='1'&&s[0]<='9')) {
			for (int sIndex = 1; sIndex < s.length(); sIndex++) {
				if (!(s[sIndex]>='0'&&s[sIndex]<='9')) return false;
			}
			return true;
		}
	}
	return false;
}

int stoi(string s) {
	bool isPrivate = false;
	int base = 1;
	int re = 0;	// result
	for (int sIndex = s.length()-1; sIndex >= 0; sIndex--) {
		if (s[sIndex]=='-'&&sIndex==0) {
			isPrivate = true;
			continue;
		} else {
			re += base*(s[sIndex]-'0');
			base *= 10;
		}
	}
	if (isPrivate) re = 0 - re;
	return re;
}

string itos(int n) {
	string s = "\0";
	bool isPrivate = false;
	if (n<0) {
		isPrivate = true;
		n = 0-n;
	}
	while (n>0) {
		char c = n%10 + '0';
		s = c+s;
		n/=10;
	}
	if (isPrivate) s = "-"+s;
	return s;
}

void DAS(string& s)    // 删除所有空格和\t
{
	int it;
	while (it = s.find(" "),it!=s.npos)
	{
		s.replace(it,1,"");
	}
	while (it = s.find("\t"),it!=s.npos)
	{
		s.replace(it,1,"");
	}
}


string getFromClient() {
	string re = "\0";
	getline(cin, re);
	DAS(re);
	return re;
}

void funcPrint() {
	cout<<"*****************************************"<<endl;
	cout<<"*    W    E    L    C    O    M    E    *"<<endl;
	cout<<"*****************************************"<<endl;
	cout<<"*     1. inquire information            *"<<endl;
	cout<<"*     2. print all card                 *"<<endl;
	cout<<"*     3. cards management               *"<<endl;
	cout<<"*     4. (un)binding to binding card    *"<<endl;
	cout<<"*     5. use a card                     *"<<endl;
	cout<<"*     9. exit the system                *"<<endl;
	cout<<"*****************************************"<<endl;
}

void pauseForRead() {
	cout<<"\n"<<"enter any key to continue..."<<endl;
	string a = getFromClient();
	system("cls");
}

