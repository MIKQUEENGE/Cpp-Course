//class_polynomial.h
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <stdlib.h>
using namespace std;

int sum = 0;                                  // the number of the polynomials

// the element of polynomial
struct poly{
	poly* next = NULL;
	int value;
	int power;
};

// class polynomial
class polynomial{
	private:
		poly* first;
		string name;
	public:
		polynomial():first(NULL),name("\0") {}
		polynomial(polynomial &p) {
			if (p.first) {
			   this->first = new poly;
			   poly* p1 = p.first;
			   first->value = p1->value;
			   first->power = p1->power;
			   poly* k = first;
			   p1 = p1->next;
			   while (p1) {
			   		k->next = new poly;
					k = k->next;
					k->value = p1->value;
					k->power = p1->power;
					p1 = p1->next;
				}
			}
			name = "\0";
		}
		~polynomial();
		poly* getFirst();
		void setName(string);
		string getName();
		int input(string);
		polynomial addition(polynomial&);
		polynomial subtraction(polynomial&);
		polynomial multiConstant(int);
		int subsValue(int);
		polynomial multiplication(polynomial&);
		int ifEqual(polynomial&);
		polynomial differentiation();
		void print();
		void better() {
			poly *f = this->first;
			while (f&&f->value==0) {
				poly *f2 = f->next;
				delete f;
				f = f2;
			}
			while(f) {
				if (f->next&&f->next->value==0) {
					poly *f2 = f->next->next;
					delete f->next;
					f->next = f2;
				}
				f = f->next;
			}
		}
		friend std::ostream& operator<<(ostream &os, polynomial &com) {
			//reload to write in file
			//like q=(5,6)(-4,3)(1,0)
			os<<com.name<<"=";
			poly *k = com.first;
			while(k) {
				os<<"("<<k->value<<","<<k->power<<")";
				k = k->next;
			}
			os<<"\0";
		}
};
//realize functions

// destructer
polynomial::~polynomial() {                         
	poly *k;
	while(this->first) {
		k = this->first;
		first = first->next;
		delete k;
	}
}

// get the point pointing the first element of the polynomial
poly* polynomial::getFirst() {                      
	return first;
}

// set the name of the polynomial
void polynomial::setName(string a) {                
	name = a;
}

// get the name of the polynomial
string polynomial::getName() {                      
	return name;
}

//when return 0, it means input is wrong
int polynomial::input(string a) {
	if (a[0] == '(') {
		int flag = 0;
		for (int i = 1; i < a.length(); i++) {
			if (!((a[i]>='0'&&a[i]<='9')||a[i]=='('||a[i]==')'||a[i]==','
			    ||a[i]=='-')||(a[i]=='('&&a[i-1]!=')')||a[a.length()-1]!=')') {
			    	return 0;
				}
			if (a[i]=='('||a[i]==')'||a[i]==',') {
				flag++;
				if (a[i]=='('&&flag%3!=0 || a[i]==','&&flag%3!=1
				    || a[i]==')'&&flag%3!=2) {
				    	return 0;
					}
			}
		}
		int mid[flag/3][2], num = 0;
		mid[0][0] = mid[0][1] = 0;
		for (int i = 0; i < a.length(); i++) {
			for (int j = i+1; j < a.length(); j++) {
				if (a[j]!=',') continue;
				for (int q = j+1; q < a.length(); q++) {
					if (a[q]!=')') continue;
					string s(a,i+1,j-i-1), t(a,j+1,q-j-1);
					sscanf(s.c_str(),"%d",&mid[num][0]);
					sscanf(t.c_str(),"%d",&mid[num][1]);
					i = q+1;
					break;
				}
				break;
			}
			num++;
		}
		for (int i = 1; i < num; i++) {
			if (mid[i][1]>=mid[i-1][1]) return 0;
		}
		this->first = new poly;
		first->value = mid[0][0];
		first->power = mid[0][1];
		poly* k = first;
		for (int i = 1; i < num; i++) {
			k->next = new poly;
			k = k->next;
			k->value = mid[i][0];
			k->power = mid[i][1];
		}
		cout<<"please name this polynomial : ";
		string na;
		cin>>na;
		setName(na);
		better();
		return 1;
	} else if ((a[0] >= 'a' && a[0] <= 'z') || (a[0] >= 'A' && a[0] <= 'Z')) {
		return 0;
	} else {
		int eq;
		for (eq = 0; eq < a.length(); eq++) {
			if (a[eq] == '=') break;
		}
		string s(a,0,eq);
		setName(s);
		int flag = 0;
		for (int i = eq+2; i < a.length(); i++) {
			if (!((a[i]>='0'&&a[i]<='9')||a[i]=='('||a[i]==')'||a[i]==','
			    ||a[i]=='-')||(a[i]=='('&&a[i-1]!=')')||a[a.length()-1]!=')') {
			    	return 0;
				}
			if (a[i]=='('||a[i]==')'||a[i]==',') {
				flag++;
				if (a[i]=='('&&flag%3!=0 || a[i]==','&&flag%3!=1
				    || a[i]==')'&&flag%3!=2) {
				    	return 0;
					}
			}
		}
		int mid[flag/3][2], num = 0;
		mid[0][0] = mid[0][1] = 0;
		for (int i = eq+1; i < a.length(); i++) {
			for (int j = i+1; j < a.length(); j++) {
				if (a[j]!=',') continue;
				for (int q = j+1; q < a.length(); q++) {
					if (a[q]!=')') continue;
					string s(a,i+1,j-i-1), t(a,j+1,q-j-1);
					sscanf(s.c_str(),"%d",&mid[num][0]);
					sscanf(t.c_str(),"%d",&mid[num][1]);
					i = q+1;
					break;
				}
				break;
			}
			num++;
		}
		for (int i = 1; i < num; i++) {
			if (mid[i][1]>=mid[i-1][1]) return 0;
		}
		this->first = new poly;
		first->value = mid[0][0];
		first->power = mid[0][1];
		poly* k = first;
		for (int i = 1; i < num; i++) {
			k->next = new poly;
			k = k->next;
			k->value = mid[i][0];
			k->power = mid[i][1];
		}
		better();
		return 1;
	}
}

polynomial polynomial::addition(polynomial& p) {
	polynomial add = p;
	poly *f1 = this->first, *f2 = add.getFirst();
	while(f1) {
		while(f2) {
			if (f1->power == f2->power) {
				f2->value+=f1->value;
				break;
			} else if (f1->power < f2->power) {
				poly *n = new poly;
				n->power = f1->power;
				n->value = f1->value;
				n->next = f2->next;
				f2->next = n;
				break;
			}
			f2 = f2->next;
		}
		f1 = f1->next;
	}
	add.better();
	return add;
}

polynomial polynomial::subtraction(polynomial& p) {
	polynomial sub = *this;
	poly *f2 = this->first, *f1 = p.getFirst();
	while(f1) {
		while(f2) {
			if (f1->power == f2->power) {
				f2->value-=f1->value;
				break;
			} else if (f1->power < f2->power) {
				poly *n = new poly;
				n->power = f1->power;
				n->value = 0 - f1->value;
				n->next = f2->next;
				f2->next = n;
				break;
			}
			f2 = f2->next;
		}
		f1 = f1->next;
	}
	sub.better();
	return sub;
}

polynomial polynomial::multiConstant(int k) {
	polynomial multi = *this;
	poly *f = multi.getFirst();
	while (f) {
		f->value *= k;
		f = f->next;
	}
	multi.better();
	return multi;
}

int polynomial::subsValue(int x) {
	int re = 0;
	poly *f = first;
	while (f) {
		re+=f->value*((int)pow(x,f->power));
		f = f->next;
	}
	return re;
}

polynomial polynomial::multiplication(polynomial& p) {
	polynomial re, k;
	poly *f1 = this->first, *f2;
	while (f1) {
		k = p.multiConstant(f1->value);
		f2 = k.getFirst();
		while (f2) {
			f2->power += f1->power;
			f2 = f2->next;
		}
		re = re.addition(k);
	}
	re.better();
	return re;
}

int polynomial::ifEqual(polynomial& p) {
	poly *f1 = this->first, *f2 = p.first;
	for ( ; ; ) {
		if (f1==NULL&&f2==NULL) return 1;
		if (f1==NULL&&f2!=NULL || f1!=NULL&&f2==NULL) return 0;
		if (f1->power!=f2->power || f1->value!=f2->value) return 0;
		f1 = f1->next;
		f2 = f2->next;
	}
}

polynomial polynomial::differentiation() {
	polynomial re = *this;
	poly *f = re.getFirst();
	while (f) {
		f->value *= f->power;
		f->power--;
		f = f->next;
	}
	re.better();
	return re;
}
//print in the form of "x^5-3x^3+5"
void polynomial::print() {
	better();
	poly *f = this->first;
	cout<<name<<"=";
	int k = 0;
	while (f) {
		if (k&&f->value>=0) cout<<'+';
		cout<<f->value<<"x^"<<f->power;
		f = f->next;
	}
	cout<<endl;
}

