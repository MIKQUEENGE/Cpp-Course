//POLYNOMIAL.cpp
#include "screen.h"

int main() {
	fstream file("polynomial_DB.txt");
	screen();
	string in;
	while (1) {
		getline(cin,in);
		if (in.length() == 1) {
			char ch = in[0];
			switch(ch)
			{
				case'1':              // input a polynomial
					{int f = 0;
					polynomial &pIn = po[sum];
					while (!f) {
						string in1;
					cout<<"input a polynomial ";
					cout<<"and ensure it's in the right form : \n";
					getline(cin,in1);
					if (in1.length()==1&&in1[0]=='*') {
						goto help;
					}
					f = pIn.input(in1);
					}
					sum++;
					cout<<"the polynomial you put in is : ";
					pIn.print();}
					break;
				case'2':             // add a polynomial
					{
					string p, q, name;
					polynomial a, b;
					cout<<"please input the name of the polynomial you want to operater: \n";
					cout<<"the first one : ";
					cin>>p;
					int f = 1;
					if (p.length()==1&&p[0]=='*') {
						goto help;
					}
					for (int i = 0; i < sum; i++) {
						if (po[i].getName() == p) {
							a = po[i];
							break;
						}
						if (i == sum && po[i].getName() != p) {
							f = 0;
						}
					}
					if (!f) {
						cout<<"the polynomial not exist! please add it first!"<<endl;
						break;
					}
					f = 1;
					cout<<"the second one : ";
					cin>>q;
					if (q.length()==1&&q[0]=='*') {
							goto help;
					}
					for (int i = 0; i < sum; i++) {
						if (po[i].getName() == q) {
							b = po[i];
							break;
						}
						if (i == sum && po[i].getName() != q) {
							f = 0;
						}
					}
					if (!f) {
						cout<<"the polynomial not exist! please add it first!"<<endl;
						break;
					}
					f = 0;			
					while (!f) 
					{
						cout<<"please input the name of the result : ";
						cin>>name;
						if (name.length()==1&&name[0]=='*') {
							goto help;
						}
						f = po[sum].input(name);
					}
					po[sum] = a.addition(b);
					f = po[sum].input(name);
					cout<<"the result of the addition is : ";
					po[sum].print();
					sum++;
					}
					break;
				case'3':   //substraction
					{
					string p, q, name;
					polynomial a, b;
					cout<<"please input the name of the polynomial you want to operater: \n";
					cout<<"the one be subtracted: ";
					cin>>p;
					int f = 1;
					if (p.length()==1&&p[0]=='*') {
						goto help;
					}
					for (int i = 0; i < sum; i++) {
						if (po[i].getName() == p) {
							a = po[i];
							break;
						}
						if (i == sum && po[i].getName() != p) {
							f = 0;
						}
					}
					if (!f) {
						cout<<"the polynomial not exist! please add it first!"<<endl;
						break;
					}
					f = 1;
					cout<<"the one subtracting : ";
					cin>>q;
					if (q.length()==1&&q[0]=='*') {
						goto help;
					}
					for (int i = 0; i < sum; i++) {
						if (po[i].getName() == q) {
							b = po[i];
							break;
						}
						if (i == sum && po[i].getName() != q) {
							f = 0;
						}
					}
					if (!f) {
						cout<<"the polynomial not exist! please add it first!"<<endl;
						break;
					}
					f = 0;			
					while (!f) 
					{
						cout<<"please input the name of the result : ";
						cin>>name;
						if (name.length()==1&&name[0]=='*') {
							goto help;
						}
						f = po[sum].input(name);
					}
					po[sum] = a.subtraction(b);
					f = po[sum].input(name);
					cout<<"the result of the subtraction is : ";
					po[sum].print();
					sum++;
					}
					break;
				case'4':                          //Multiply    a     constant
					{
					string p, q, name;
					int multi;
					polynomial a;
					cout<<"please input the name of the polynomials and the content you want to operater: \n";
					cout<<"the polynomial  : ";
					cin>>p;
					int f = 1;
					if (p.length()==1&&p[0]=='*') {
						goto help;
					}
					for (int i = 0; i < sum; i++) {
						if (po[i].getName() == p) {
							a = po[i];
							break;
						}
						if (i == sum && po[i].getName() != p) {
							f = 0;
						}
					}
					if (!f) {
						cout<<"the polynomial not exist! please add it first!"<<endl;
						break;
					}
					f = 1;
					cout<<"the content : ";
					cin>>q;
					if (q.length()==1&&q[0]=='*') {
						goto help;
					}
					for (int k = 0; k < q.length(); k++) {
						if (q[k] < '0' ||q[k] > '9') {
							f = 0;
							break;
						}
					}
					if (!f) {
						cout<<"your input is not an integer!"<<endl;
						break;
					}
					multi = atoi(q.c_str());
					f = 0;			
					while (!f) 
					{
						cout<<"please input the name of the result : ";
						cin>>name;
						if (name.length()==1&&name[0]=='*') {
							goto help;
						}
						f = po[sum].input(name);
					}
					po[sum] = a.multiConstant(multi);
					f = po[sum].input(name);
					cout<<"the result  is : ";
					po[sum].print();
					sum++;
					}
					break;
				case'5':                 //Substitute     a     value
					{
					string p, q, name;
					int m;
					polynomial a;
					cout<<"please input the name of the polynomial and the value you want to operater: \n";
					cout<<"the polynomial  : ";
					cin>>p;
					int f = 1;
					if (p.length()==1&&p[0]=='*') {
						goto help;
					}
					for (int i = 0; i < sum; i++) {
						if (po[i].getName() == p) {
							a = po[i];
							break;
						}
						if (i == sum && po[i].getName() != p) {
							f = 0;
						}
					}
					if (!f) {
						cout<<"the polynomial not exist! please add it first!"<<endl;
						break;
					}
					f = 1;
					cout<<"the value : ";
					cin>>q;
					if (q.length()==1&&q[0]=='*') {
						goto help;
					}
					for (int k = 0; k < q.length(); k++) {
						if (q[k] < '0' ||q[k] > '9') {
							f = 0;
							break;
						}
					}
					if (!f) {
						cout<<"your input is not an integer!"<<endl;
						break;
					}
					m = atoi(q.c_str());
					int re = a.subsValue(m);
					cout<<"the result  is : "<<re<<endl;
					}
					break;
				case'6':         //Print    all    polynomial
					{
					cout<<"the sum is :"<<sum<<endl;
					for (int k = 0; k < sum; k++) {
						po[k].print();
					}
					}
					break;
				case'7':         //Polynomial  multiplication
					{
					string p, q, name;
					polynomial a, b;
					cout<<"please input the name of the polynomials you want to operater: \n";
					cout<<"the first one : ";
					cin>>p;
					int f = 1;
					if (p.length()==1&&p[0]=='*') {
						goto help;
					}
					for (int i = 0; i < sum; i++) {
						if (po[i].getName() == p) {
							a = po[i];
							break;
						}
						if (i == sum && po[i].getName() != p) {
							f = 0;
						}
					}
					if (!f) {
						cout<<"the polynomial not exist! please add it first!"<<endl;
						break;
					}
					f = 1;
					cout<<"the second one: ";
					cin>>q;
					if (q.length()==1&&q[0]=='*') {
						goto help;
					}
					for (int i = 0; i < sum; i++) {
						if (po[i].getName() == q) {
							b = po[i];
							break;
						}
						if (i == sum && po[i].getName() != q) {
							f = 0;
						}
					}
					if (!f) {
						cout<<"the polynomial not exist! please add it first!"<<endl;
						break;
					}
					f = 0;			
					while (!f) 
					{
						cout<<"please input the name of the result : ";
						cin>>name;
						if (name.length()==1&&name[0]=='*') {
							goto help;
						}
						f = po[sum].input(name);
					}
					po[sum] = a.multiplication(b);
					f = po[sum].input(name);
					cout<<"the result is : ";
					po[sum].print();
					sum++;
					}
					break;
				case'8':                //Equal             judgment 
					{
					string p, q, name;
					polynomial a, b;
					cout<<"please input the name of the polynomials you want to compare: \n";
					cout<<"the first one : ";
					cin>>p;
					int f = 1;
					if (p.length()==1&&p[0]=='*') {
						goto help;
					}
					for (int i = 0; i < sum; i++) {
						if (po[i].getName() == p) {
							a = po[i];
							break;
						}
						if (i == sum && po[i].getName() != p) {
							f = 0;
						}
					}
					if (!f) {
						cout<<"the polynomial not exist! please add it first!"<<endl;
						break;
					}
					f = 1;
					cout<<"the second one: ";
					cin>>q;
					if (q.length()==1&&q[0]=='*') {
						goto help;
					}
					for (int i = 0; i < sum; i++) {
						if (po[i].getName() == q) {
							b = po[i];
							break;
						}
						if (i == sum && po[i].getName() != q) {
							f = 0;
						}
					}
					if (!f) {
						cout<<"the polynomial not exist! please add it first!"<<endl;
						break;
					}
					f = 0;			
					while (!f) 
					{
						cout<<"please input the name of the result : ";
						cin>>name;
						if (name.length()==1&&name[0]=='*') {
							goto help;
						}
						f = po[sum].input(name);
					}
					int re = a.ifEqual(b);
					if (re) cout<<"YES!"<<endl;
					else cout<<"NO!"<<endl;
					}
					break;
				case'9':                        //Polynomial differentiation
					{
					string p, name;
					polynomial a;
					cout<<"please input the name of the polynomials you want to operater: \n";
					cin>>p;
					int f = 1;
					if (p.length()==1&&p[0]=='*') {
						goto help;
					}
					for (int i = 0; i < sum; i++) {
						if (po[i].getName() == p) {
							a = po[i];
							break;
						}
						if (i == sum && po[i].getName() != p) {
							f = 0;
						}
					}
					if (!f) {
						cout<<"the polynomial not exist! please add it first!"<<endl;
						break;
					}
					f = 0;			
					while (!f) 
					{
						cout<<"please input the name of the result : ";
						cin>>name;
						if (name.length()==1&&name[0]=='*') {
							goto help;
						}
						f = po[sum].input(name);
					}
					po[sum] = a.differentiation();
					f = po[sum].input(name);
					cout<<"the result is : ";
					po[sum].print();
					sum++;
					}
					break;
				case'0':
					return 0;
				help:
				case'*':
					screen();
					break;
			}
		} else {
			cout<<"invalid input!"<<endl;
		}
	}
	return 0;
}
