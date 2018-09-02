#include <iostream>       
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

#define max 100
int sum = 0;
int stoi(string s);      	// �ַ���ת����
int pow(int a, int b);		// a��b�η�
void founctions_screen();
void loop();
void cmd();
void read();
void write();
void DAS(string&);      // delete add spacesɾ�����пո�

class polynomial		// ����ʽ��
{
private:
	string name;		// ����ʽ�����֣�����p
	int poly[max][2];
	int num;        
public:
	polynomial()       // ���캯��
	{
		for (int i = 0; i < max; i++) for (int j = 0; j < 2; j++) poly[i][j] = 0;
		num = 0;
		name = "\0";
	}
	polynomial(const polynomial &p)       // ��������
	{
		name = p.name;
		for (int i = 0; i < max; i++) for (int j = 0; j < 2; j++) poly[i][j] = p.poly[i][j];
		num = p.num;
	}
	~polynomial() {}                  // ��������
	int getNum() const
	{
		return num;
	}
	void setNum(const int n)
	{
		num = n;
	}
	void setName(const string s)           // ������
	{
		name = s;
	}
	string getName() const               // �������
	{
		return name;
	}
	void input(string);             		// �û�����
	void build(int, string);						// �ѻ�ȡ����Ϣ���ݵ�����ʽ��
	polynomial add(polynomial&);		// ��
	polynomial subtract(polynomial&);   // ��
	polynomial multiConstant(int);      // �˳���
	int subsValue(int);                 // ���볣��
	polynomial multiplication(polynomial&);     // ��
	int ifEqual(polynomial&);       // �ж����
	polynomial differentiation();   // ��
	void print();                   // �Ѻô�ӡ
	
	//���������
	polynomial operator+(polynomial &p)
	{
		return add(p);
	}
	polynomial operator-(polynomial &p)
	{
		return subtract(p);
	}
	polynomial operator*(polynomial &p)
	{
		return multiplication(p);
	}
	friend istream& operator>>(istream& is, polynomial &p)
	{
		string k;
		is>>k;
		p.name = k;
		is>>p.num;
		for (int i = 0; i < p.num; i++) is>>p.poly[i][0]>>p.poly[i][1];
		return is;
	}
	friend ostream& operator<<(ostream& os, polynomial &p)
	{
		DAS(p.name);
		os<<p.name<<'\n'<<p.num<<' ';
		for (int i = 0; i < p.num; i++)
		if (i!=p.num-1)os<<p.poly[i][0]<<' '<<p.poly[i][1]<<' ';
		else os<<p.poly[i][0]<<' '<<p.poly[i][1]<<'\n';
		return os;
	}
};

polynomial repo[max];   // ���ڴ洢����ʽ


int main()					 // ������
{
	read();
	founctions_screen();
	loop();
	write();
	return 0;
}



int stoi(string s)      // �ַ���ת����
{
	int is_p = 0;
	int l = s.length();
	int re = 0, m = 1;
	for (int i = l-1; i >= 0; i--)
	{
		if (s[i] == '-') {
			is_p = 1;
			break;
		}
		re+=(s[i]-'0')*m;
		m*=10;
	}
	if (is_p) re = -re;
	return re;
}



int pow(int a, int b)	// a��b�η�
{
	int re = 1;
	for (int i = 1; i <= b; i++) re*=a;
	return re;
}

int isR(int pos, string a)            // �ж��û��Ƿ��������
{
	int isR_f = 0;
	int m = pos;
	for (int i = pos; i < a.length(); i++)
	{
		if (a[i]!='(' && a[i]!=')' && a[i]!=',' && (a[i]<'0'||a[i]>'9') && a[i]!='-')
		{
			return 0;
		}
		if (i != pos && (a[i] == '(' && a[i-1] != ')'))
		{
			return 0;
		}
		if (a[i]==','&&(a[i-1]=='('||a[i+1]==')'))
		{
			return 0;
		}
		if (a[i]=='(' || a[i]==')' || a[i]==',')
		{
			isR_f++;
			if (isR_f > max*3) {
				cout<<"�������������࣡��ȷ���������������"<<max<<"!"<<endl;
				return 0;
			}
			if (i - m - 1 >= 10) {
				cout<<"�������ִ�С������Χ�����ַ�ΧΪ-99999999~999999999"<<endl;
				return 0;
			}
			m = i;
			if ((a[i]=='('&&isR_f%3!=1)||(a[i]==','&&isR_f%3!=2)||(a[i]==')'&&isR_f%3!=0))
			{
				return 0;
			}
		}
	}
	return 1;
}

void polynomial::build(int pos, string a)
{
	int l = a.length();
	string s1, s2;
	int have_print_nosort = 0;
	int ln[max],mn[max],rn[max];
	int i = 0, j = 0, t = 0;
	for (int q = 0; q < l; q++)
	{
		if (a[q]=='(')
		{
			ln[i] = q;
			i++;
		}
		if (a[q]==',')
		{
			mn[j] = q;
			j++;
		}
		if (a[q]==')')
		{
			rn[t] = q;
			t++;
		}
	}
	for (int p = 0; p < i; p++)                 // Ѱ�Ҳ�������������
	{
		s1 = a.substr(ln[p]+1, mn[p]-ln[p]-1);
		s2 = a.substr(mn[p]+1,rn[p]-mn[p]-1);
		poly[num][0] = stoi(s1);
		poly[num][1] = stoi(s2);
		num++;
	}
	int x;
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num-1; j++)
		{
			if (poly[j][1] < poly[j+1][1])
			{
				if (!have_print_nosort)   	// ��ӡδ������ʾ��
				{
					cout<<"��������δ����ϵͳ���Զ���������"<<endl;
					have_print_nosort = 1;
				}
				x = poly[j][1];
				poly[j][1] = poly[j+1][1];
				poly[j+1][1] = x;
				x = poly[j][0];
				poly[j][0] = poly[j+1][0];
				poly[j+1][0] = x;
			}
		}
	}
	int ever_equal = 0;
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num-1; j++)
		{
			if (poly[j][1] == poly[j+1][1])
			{
				if (!ever_equal)
				{
					cout<<"������Ĳ�����������ȣ�ϵͳ�Ѱ����Զ��ϲ���"<<endl;
					ever_equal = 1;
				}
				poly[j][0] += poly[j+1][0];
				for (int k = j+1; k < num-1; k++)
				{
					poly[k][0] = poly[k+1][0];
					poly[k][1] = poly[k+1][1];
				}
				num--;
			}
			if (poly[j][0] == 0)
			{
				for (int k = j; k < num-1; k++)
				{
					poly[k][0] = poly[k+1][0];
					poly[k][1] = poly[k+1][1];
				}
				num--;
			}
		}
	}
}

void polynomial::input(string a)             		// �û�����
{
	DAS(a);
	if (a.compare("0")==0) {write();exit(0);}
	if (a.compare("9")==0)
	{
		founctions_screen();
		loop();
		write();
		exit(0);
	}
	int l = a.length();
	if (a[0]=='(')
	{
		if (!isR(0,a))
		{
			cout<<"�����ʽ�������������룡"<<endl;
			string a_input;
			getline(cin,a_input);
			DAS(a_input);
			if (a_input.compare("0")==0) {
				write();
				exit(0);
			}
			if (a_input.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
			input(a_input);			
			return;
		} else {
			build(0,a);
			cout<<"�Ƿ��뱣��˶���ʽ����������1����������������"<<endl;
			string ifName;
			getline(cin,ifName);
			DAS(ifName);
			if (ifName.compare("0")==0) 
			{
				write();
				exit(0);
			}
			if (ifName.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
			if (ifName=="1")		// �Ա���Ķ���ʽ������������
			{
				cout<<"������:"<<endl;
				while (1)
				{
					string inName;
					getline(cin,inName);
					DAS(inName);
					if (inName.compare("0")==0) {write();exit(0);}
					if (inName.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
					if ((inName[0]<'a'||inName[0]>'z')&&(inName[0]<'A'||inName[0]>'Z'))
					{
						cout<<"���ֱ�����Ӣ����ĸ��ͷ��ֻ����Ӣ�ĺ����֣�"<<endl;
						continue;
					} else {
						int nameR = 1;
						for (int i = 0; i < inName.length(); i++)
						{
							if ((inName[i]<'0'||inName[i]>'9')&&(inName[i]<'a'||inName[i]>'z')&&(inName[i]<'A'||inName[i]>'Z'))
							{
								cout<<"���ֱ�����Ӣ����ĸ��ͷ��ֻ����Ӣ�ĺ����֣�"<<endl;
								nameR = 0;
								break;
							}
						}
						for (int i = 0; i < sum; i++)
						{
							if (repo[i].getName() == inName)
							{
								cout<<"�������ѱ�ռ�ã����������룺"<<endl;
								nameR = 0;
								break;
							}
						}
						if (!nameR) continue;
						if (nameR)
						{
							setName(inName);
							break;
						}
					}
				}
			}
			return;
		}
	} else {
		if ((a[0]<'a'||a[0]>'z')&&(a[0]<'A'||a[0]>'Z'))
		{
			cout<<"���ֱ�����Ӣ����ĸ��ͷ��ֻ����Ӣ�ĺ����֣�"<<endl;
			string a_input;
			getline(cin,a_input);
			DAS(a_input);
			if (a_input.compare("0")==0) {write();exit(0);}
			if (a_input.compare("9")==0)
			{
				founctions_screen();
				loop();
				write();
				exit(0);
			}
			input(a_input);
			return;
		} else {
			int epos = 0;
			while (a[epos]!='=') {
				epos++;
				if (epos>=a.length()-5) {
					cout<<"�����ʽ�������������룡"<<endl;
					string a_input;
					getline(cin,a_input);
					DAS(a_input);
					if (a_input.compare("0")==0) {write();exit(0);}
					if (a_input.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
					input(a_input);
					return;
				}
			}
			if (!isR(epos+1,a))
			{
				cout<<"�����ʽ�������������룡"<<endl;
				string a_input;
				getline(cin,a_input);
				DAS(a_input);
				if (a_input.compare("0")==0) {write();exit(0);}
				if (a_input.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
				input(a_input);			
				return;
			} else {
				int right = 1;
				string x = a.substr(0, epos);
				for (int i = 0; i < sum; i++)
				{
					if (repo[i].getName() == x)
					{
						cout<<"�������ѱ�ռ�ã����������룺"<<endl;
						right = 0;
						string a_in;
						getline(cin,a_in);
						DAS(a_in);
						input(a_in);
						break;
					}
				}
				if (right)
				{
					name = x;
					build(epos+1,a);
					return;
				}
			}
		}
	}
}

polynomial polynomial::add(polynomial &addpoly)		// ��
{	
	polynomial re;
	re.name = "\0";
	int i = 0, j = 0, k = 0;
	while (i < num||j < addpoly.num)
	{
		if (j >= addpoly.num)
		{
			while (i < num)
			{
				re.poly[k][0] = poly[i][0];
				re.poly[k][1] = poly[i][1];
				i++;
				k++;
			}
			break;
		}
		if (i >= num)
		{
			while (j < addpoly.num)
			{
				re.poly[k][0] = addpoly.poly[j][0];
				re.poly[k][1] = addpoly.poly[j][1];
				j++;
				k++;
			}
			break;
		}
		if (poly[i][1] == addpoly.poly[j][1])
		{
			re.poly[k][0] = poly[i][0] + addpoly.poly[j][0];
			re.poly[k][1] = poly[i][1];
			i++;
			j++;
			k++;
		} else if (poly[i][1] > addpoly.poly[j][1]) {
			re.poly[k][0] = poly[i][0];
			re.poly[k][1] = poly[i][1];
			i++;
			k++;
		} else if (poly[i][1] < addpoly.poly[j][1]) {
			re.poly[k][0] = addpoly.poly[j][0];
			re.poly[k][1] = addpoly.poly[j][1];
			j++;
			k++;
		}
	}
	re.num = k;
	return re;
}

polynomial polynomial::subtract(polynomial &subtpoly)   // ��
{
	polynomial spoly = subtpoly;
	for (int i = 0; i < spoly.getNum(); i++)
	{
		spoly.poly[i][0] = 0-spoly.poly[i][0];
	}
	polynomial a = add(spoly);
	a.setName("\0");
	return a;
}

polynomial polynomial::multiConstant(int c)      // �˳���
{
	polynomial re = *this;
	for (int i = 0; i < re.getNum(); i++)
	{
		re.poly[i][0] *= c;
	}
	return re;
}

int polynomial::subsValue(int v)                 // ���볣��
{
	int re = 0;
	for (int i = 0; i < num; i++)
	{
		re+=(poly[i][0]*(pow(v,poly[i][1])));
	}
	return re;
}

polynomial polynomial::multiplication(polynomial &multipoly)     // ��
{
	polynomial re;
	for (int i = 0; i < num; i++)
	{
		polynomial po = multipoly;
		for (int j = 0; j < po.getNum(); j++)
		{
			po.poly[j][0]*=poly[i][0];
			po.poly[j][1]+=poly[i][1];
		}
		re = re.add(po);
	}
	re.setName("\0");
	return re;
}

int polynomial::ifEqual(polynomial& epoly)       // �ж����
{
	if (num != epoly.num) return 0;
	int i = 0;
	while (1)
	{
		if (i == num) return 1;
		if ((poly[i][0]!=epoly.poly[i][0]) || (poly[i][1]!=epoly.poly[i][1])) return 0;
		i++;
	}
}

polynomial polynomial::differentiation()   // ��
{
	polynomial re = *this;
	for (int i = 0; i < num; i++)
	{
		re.poly[i][0]*=re.poly[i][1];
		re.poly[i][1]--;
	}
	re.setName("\0");
	return re;
}

void polynomial::print()                   // �Ѻô�ӡ
{
	if (name.length()!=0) cout<<name<<'=';
	for (int i = 0; i< num; i++)
	{
		if (num == 1 && poly[0][0] == 0) cout<<"0"<<endl;
		if (poly[i][0]!=0)
		{
			if (i!=0&&(poly[i][0])>0) cout<<'+';
			if ((poly[i][0])!=1 && (poly[i][0])!=-1 || poly[i][1]==0) cout<<poly[i][0];
			else if (poly[i][0] == -1) cout<<'-';
			if (poly[i][1]==1) cout<<'x';
			else if (poly[i][1]!=0) cout<<"x^"<<poly[i][1];
		}
	}
	cout<<endl;
}

void founctions_screen()				// ��ӡ���ܱ�
{
	cout<<"-------------------------------\n";
	cout<<"|         ����ʽ������        |\n";
	cout<<"-------------------------------\n";
	cout<<"\n";
	cout<<"*******************************\n";
	cout<<"*    ----  �����б�  ----     *\n";
	cout<<"*  1.      �������ʽ         *\n";
	cout<<"*  2.     ����ʽ�Ӽ���        *\n";
	cout<<"*  3. ����ʽ�볣���ĳ˷�����  *\n";
	cout<<"*  4.  �����ʽ����ĳ���ֵ   *\n";
	cout<<"*  5. �ж���������ʽ�Ƿ����  *\n";
	cout<<"*  6.  ��ʾ���д������ʽ     *\n";
	cout<<"*  7.   ��ĳ������ʽ��      *\n";
	cout<<"*  8.    ����������ģʽ       *\n";
	cout<<"*  9.  ����(�鿴�����б�)     *\n";
	cout<<"*  0.       �˳�ϵͳ          *\n";
	cout<<"*******************************\n";
}

void print_all()
{
	if (sum == 0)
	{
		cout<<"û���Ѵ洢�Ķ���ʽ��";
	} else {
		cout<<"Ŀǰ�Ѵ洢��"<<sum<<"������ʽ��"<<endl;
		for (int i = 0; i < sum; i++)
		{
			repo[i].print();
		}
	}
}

int find_poly(string n)                  			// �ڲֿ���Ѱ�Ҷ���ʽ
{
	for (int i = 0; i < sum; i++)
	{
		string n1 = repo[i].getName();
		if (n1.compare(n)==0) return i;
	}
	return -1;
}

void if_save(polynomial &p)
{
	cout<<"�Ƿ��뱣��˶���ʽ����������1����������������"<<endl;
	string ifName;
	getline(cin,ifName);
	DAS(ifName);
	if (ifName.compare("0")==0) {write();exit(0);}
	if (ifName.compare("9")==0)
	{
		founctions_screen();
		loop();
		write();
		exit(0);
	}
	if (ifName=="1")		// �Ա���Ķ���ʽ������������
	{
		cout<<"������:"<<endl;
		while (1)
		{
			string inName;
			getline(cin,inName);
			DAS(inName);
			if (inName.compare("0")==0) {write();exit(0);}
			if (inName.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
			if ((inName[0]<'a'||inName[0]>'z')&&(inName[0]<'A'||inName[0]>'Z'))
			{
				cout<<"���ֱ�����Ӣ����ĸ��ͷ��ֻ����Ӣ�ĺ����֣�"<<endl;
				continue;
			} else {
				int nameR = 1;
				for (int i = 0; i < inName.length(); i++)
				{
					if ((inName[i]<'0'||inName[i]>'9')&&(inName[i]<'a'||inName[i]>'z')&&(inName[i]<'A'||inName[i]>'Z'))
					{
						cout<<"���ֱ�����Ӣ����ĸ��ͷ��ֻ����Ӣ�ĺ����֣�"<<endl;
						nameR = 0;
						break;
					}
				}
				for (int i = 0; i < sum; i++)
				{
					if (repo[i].getName() == inName)
					{
						cout<<"�������ѱ�ռ�ã����������룺"<<endl;
						nameR = 0;
						break;
					}
				}
				if (nameR)
				{
					p.setName(inName);
					break;
				}
			}
		}
	} else {
		p.setName("\0");
	}
}

void loop()
{
	cout<<"��ѡ�������ܣ�"<<endl;
	string client_input;
	getline(cin, client_input);
	DAS(client_input);
	if (client_input.length()!=1 || client_input[0]<'0' || client_input[0]>'9')
	{
		cout<<"���������������������룡"<<endl;
	} else {
	int c = client_input[0]-'0';
	if (c == 0) return;
	switch(c)
	{
		case 1:
		{
			if (sum >= max)
			{
				cout<<"�ֿ��������볢���������ܣ�"<<endl;
				break;
			}
			cout<<"��������Ҫ��ӵĶ���ʽ��"<<endl;
			string one_input;
			getline(cin,one_input);
			DAS(one_input);
			if (one_input.compare("0")==0) {write();exit(0);}
			if (one_input.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
			polynomial po_input;
			po_input.input(one_input);
			cout<<"������Ķ���ʽΪ��"<<endl;
			po_input.print();
			if (po_input.getName()!="\0")
			{
				repo[sum] = po_input;
				sum++;
			}
			break;
		}
		case 2:
		{
			while (1)
			{
				cout<<"��ѡ��"<<endl;
				cout<<"1. ��    2. ��   3. ��"<<endl;
				string one_input;
				getline(cin,one_input);
				DAS(one_input);
				if (one_input == "0")
				{
					write();
					exit(0);
				} else if (one_input == "9") {
					founctions_screen();
					break;
				} else if (one_input == "1") {
					cout<<"�������һ������ʽ��"<<endl;
					string add_a;
					polynomial add_x;
					getline(cin, add_a);
					DAS(add_a);
					if (add_a.compare("0")==0) {write();exit(0);}
					if (add_a.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
					if (add_a[0]=='(')
					{
						add_x.input(add_a);
						if (add_x.getName()!="\0")
						{
							if (sum >= max)
							{
								cout<<"�Բ����޷�����!���������"<<endl;
							} else {
								repo[sum] = add_x;
								sum++;
							}
						}
					} else {
						int pos = find_poly(add_a);
						if (pos<0)
						{
							cout<<"����ʽ�����ڣ������ԣ�"<<endl;
							continue;
						} else {
							add_x = repo[pos];
						}
					}
					cout<<"������ڶ�������ʽ��"<<endl;
					string add_b;
					polynomial add_y;
					getline(cin, add_b);
					DAS(add_b);
					if (add_b.compare("0")==0) {write();exit(0);}
					if (add_b.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
					if (add_b[0]=='(')
					{
						add_y.input(add_b);
						if (add_y.getName()!="\0")
						{
							if (sum >= max)
							{
								cout<<"�Բ����޷�����!���������"<<endl;
							} else {
								repo[sum] = add_y;
								sum++;
							}
						}
					} else {
						int pos = find_poly(add_b);
						if (pos<0)
						{
							cout<<"����ʽ�����ڣ������ԣ�"<<endl;
							continue;
						} else {
							add_y = repo[pos];
						}
					}
				//	cout<<"HHH\n";
					polynomial add_re = add_x.add(add_y);
				//	cout<<"HHH\n";
					if_save(add_re);
					if (add_re.getName().length()!=0)
					{
						if (sum >= max)
						{
							cout<<"�Բ����޷�����!���������"<<endl;
						} else {
							repo[sum] = add_re;
							sum++;
						}
					}
					cout<<"��������ʽ�ĺ�Ϊ��"<<endl;
					add_re.print();
					break;
				} else if (one_input == "2") {
					cout<<"�����뱻������"<<endl;
					string add_a;
					polynomial add_x;
					getline(cin, add_a);
					DAS(add_a);
					if (add_a.compare("0")==0) {write();exit(0);}
					if (add_a.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
					if (add_a[0]=='(')
					{
						add_x.input(add_a);
						if (add_x.getName().length()!=0)
						{
							if (sum >= max)
							{
								cout<<"�Բ����޷�����!���������"<<endl;
							} else {
								repo[sum] = add_x;
								sum++;
							}
						}
					} else {
						int pos = find_poly(add_a);
						if (pos<0)
						{
							cout<<"����ʽ�����ڣ������ԣ�"<<endl;
							continue;
						} else {
							add_x = repo[pos];
						}
					}
					cout<<"�����������"<<endl;
					string add_b;
					polynomial add_y;
					getline(cin, add_b);
					DAS(add_b);
					if (add_b.compare("0")==0) {write();exit(0);}
					if (add_b.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
					if (add_b[0]=='(')
					{
						add_y.input(add_b);
						if (add_y.getName()!="\0")
						{
							if (sum >= max)
							{
								cout<<"�Բ����޷�����!���������"<<endl;
							} else {
								repo[sum] = add_y;
								sum++;
							}
						}
					} else {
						int pos = find_poly(add_b);
						if (pos<0)
						{
							cout<<"����ʽ�����ڣ������ԣ�"<<endl;
							continue;
						} else {
							add_y = repo[pos];
						}
					}
					polynomial add_re;
					add_re = add_x.subtract(add_y);
					if_save(add_re);
					if (add_re.getName()!="\0")
					{
						if (sum >= max)
						{
							cout<<"�Բ����޷�����!���������"<<endl;
						} else {
							repo[sum] = add_re;
							sum++;
						}
					}
					cout<<"��������ʽ�Ĳ�Ϊ��"<<endl;
					add_re.print();
					break;
				} else if (one_input == "3") {
					cout<<"�������һ������ʽ��"<<endl;
					string add_a;
					polynomial add_x;
					getline(cin, add_a);
					DAS(add_a);
					if (add_a.compare("0")==0) {write();exit(0);}
					if (add_a.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
					if (add_a[0]=='(')
					{
						add_x.input(add_a);
						if (add_x.getName().length()!=0)
						{
							if (sum >= max)
							{
								cout<<"�Բ����޷�����!���������"<<endl;
							} else {
								repo[sum] = add_x;
								sum++;
							}
						}
					} else {
						int pos = find_poly(add_a);
						if (pos<0)
						{
							cout<<"����ʽ�����ڣ������ԣ�"<<endl;
							continue;
						} else {
							add_x = repo[pos];
						}
					}
					cout<<"������ڶ�������ʽ��"<<endl;
					string add_b;
					polynomial add_y;
					getline(cin, add_b);
					DAS(add_b);
					if (add_b.compare("0")==0) {write();exit(0);}
					if (add_b.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
					if (add_b[0]=='(')
					{
						add_y.input(add_b);
						if (add_y.getName().length()!=0)
						{
							if (sum >= max)
							{
								cout<<"�Բ����޷�����!���������"<<endl;
							} else {
								repo[sum] = add_y;
								sum++;
							}
						}
					} else {
						int pos = find_poly(add_b);
						if (pos<0)
						{
							cout<<"����ʽ�����ڣ������ԣ�"<<endl;
							continue;
						} else {
							add_y = repo[pos];
						}
					}
					polynomial add_re;
					add_re = add_x.multiplication(add_y);
					if_save(add_re);
					if (add_re.getName()!="\0")
					{
						if (sum >= max)
						{
							cout<<"�Բ����޷�����!���������"<<endl;
						} else {
							repo[sum] = add_re;
							sum++;
						}
					}
					cout<<"��������ʽ�Ļ�Ϊ��"<<endl;
					add_re.print();
					break;
				} else {
					cout<<"û���������ѡ����������룡"<<endl;
				}
			}
			break;
		}
		case 3:
		{
			cout<<"���������ʽ��"<<endl;
			string add_a;
			polynomial add_x;
			getline(cin, add_a);
			DAS(add_a);
			if (add_a.compare("0")==0) {write();exit(0);}
			if (add_a.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
			if (add_a[0]=='(')
			{
				add_x.input(add_a);
				if (add_x.getName()!="\0")
				{
					if (sum >= max)
					{
						cout<<"�Բ����޷�����!���������"<<endl;
					} else {
						repo[sum] = add_x;
						sum++;
					}
				}
			} else {
				int pos = find_poly(add_a);
				if (pos<0)
				{
					cout<<"����ʽ�����ڣ������ԣ�"<<endl;
					break;
				} else {
					add_x = repo[pos];
				}
			}
			cout<<"�����볣����"<<endl;
			string add_b;
			getline(cin, add_b);
			DAS(add_b);
			if (add_b.compare("0")==0) {write();exit(0);}
			if (add_b.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
			int b_isR = 1;
			for (int i = 0; i < add_b.length(); i++)
			{
				if (add_b[i]<'0' || add_b[i]>'9')
				{
					cout<<"������Ĳ��������������ԣ�"<<endl;
					b_isR = 0;
					break;
				}
			}
			if (!b_isR) break;
			int c = stoi(add_b);
			polynomial add_re;			
			add_re = add_x.multiConstant(c);
			if_save(add_re);
			if (add_re.getName()!="\0")
			{
				if (sum >= max)
				{
					cout<<"�Բ����޷�����!���������"<<endl;
				} else {
					repo[sum] = add_re;
					sum++;
				}
			}
			cout<<"��Ϊ��"<<endl;
			add_re.print();
			break;
		}
		case 4:
		{
			cout<<"���������ʽ��"<<endl;
			string add_a;
			polynomial add_x;
			getline(cin, add_a);
			DAS(add_a);
			if (add_a.compare("0")==0) {write();exit(0);}
			if (add_a.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
			if (add_a[0]=='(')
			{
				add_x.input(add_a);
				if (add_x.getName().length()!=0)
				{
					if (sum >= max)
					{
						cout<<"�Բ����޷�����!���������"<<endl;
					} else {
						repo[sum] = add_x;
						sum++;
					}
				}
			} else {
				int pos = find_poly(add_a);
				if (pos<0)
				{
					cout<<"����ʽ�����ڣ������ԣ�"<<endl;
					break;
				} else {
					add_x = repo[pos];
				}
			}
			cout<<"�����볣����"<<endl;
			string add_b;
			getline(cin, add_b);
			DAS(add_b);
			if (add_b.compare("0")==0) {write();exit(0);}
			if (add_b.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
			int b_isR = 1;
			for (int i = 0; i < add_b.length(); i++)
			{
				if (add_b[i]<'0' || add_b[i]>'9')
				{
					cout<<"������Ĳ��������������ԣ�"<<endl;
					b_isR = 0;
					break;
				}
			}
			if (!b_isR) break;
			int c = stoi(add_b);
			int add_re;			
			add_re = add_x.subsValue(c);
			cout<<"���Ϊ��"<<add_re<<endl;
			break;
		}
		case 5:
		{
			cout<<"�������һ������ʽ��"<<endl;
			string add_a;
			polynomial add_x;
			getline(cin, add_a);
			DAS(add_a);
			if (add_a.compare("0")==0) {write();exit(0);}
			if (add_a.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
			if (add_a[0]=='(')
			{
				add_x.input(add_a);
				if (add_x.getName().length()!=0)
				{
					if (sum >= max)
					{
						cout<<"�Բ����޷�����!���������"<<endl;
					} else {
						repo[sum] = add_x;
						sum++;
					}
				}
			} else {
				int pos = find_poly(add_a);
				if (pos<0)
				{
					cout<<"����ʽ�����ڣ������ԣ�"<<endl;
					break;
				} else {
					add_x = repo[pos];
				}
			}
			cout<<"������ڶ�������ʽ��"<<endl;
			string add_b;
			polynomial add_y;
			getline(cin, add_b);
			DAS(add_b);
			if (add_b.compare("0")==0) {write();exit(0);}
			if (add_b.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
			if (add_b[0]=='(')
			{
				add_y.input(add_b);
				if (add_y.getName().length()!=0)
				{
					if (sum >= max)
					{
						cout<<"�Բ����޷�����!���������"<<endl;
					} else {
						repo[sum] = add_y;
						sum++;
					}
				}
			} else {
				int pos = find_poly(add_b);
				if (pos<0)
				{
					cout<<"����ʽ�����ڣ������ԣ�"<<endl;
					break;
				} else {
					add_y = repo[pos];
				}
			}
			int add_re;
			add_re = add_x.ifEqual(add_y);
			if (add_re) cout<<"���"<<endl;
			else cout<<"����"<<endl;
			break;
		}
		case 6:
		{
			print_all();
			break;
		}
		case 7:
		{
			cout<<"������Ҫ�󵼵Ķ���ʽ��"<<endl;
			string add_a;
			polynomial add_x;
			getline(cin, add_a);
			DAS(add_a);
			if (add_a.compare("0")==0) {write();exit(0);}
			if (add_a.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
			if (add_a[0]=='(')
			{
				add_x.input(add_a);
				if (add_x.getName().length()!=0)
				{
					if (sum >= max)
					{
						cout<<"�Բ����޷�����!���������"<<endl;
					} else {
						repo[sum] = add_x;
						sum++;
					}
				}
			} else {
				int pos = find_poly(add_a);
				if (pos<0)
				{
					cout<<"����ʽ�����ڣ������ԣ�"<<endl;
					break;
				} else {
					add_x = repo[pos];
				}
			}
			polynomial add_re;			
			add_re = add_x.differentiation();
			if_save(add_re);
			if (add_re.getName().compare("\0")!=0)
			{
				if (sum >= max)
				{
					cout<<"�Բ����޷�����!���������"<<endl;
				} else {
					repo[sum] = add_re;
					sum++;
				}
			}
			cout<<"�󵼺�Ϊ��"<<endl;
			add_re.print();
			break;
		}
		case 8:
		{
			system("cls");
			cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
			cout<<"  ����������ģʽ����������exit()�˳�������ģʽ"<<endl;
			cout<<"Ϊ������������������������ṩ0������9���ع��ܱ�"<<endl;
			cout<<"  Ҫ���ж���ʽ����ʱ���ȱ��棬�������ʾ����"<<endl;
			cout<<"   ����all()    :     ��ӡ���вֿ��еĶ���ʽ"<<endl;
			cout<<"   ����help()   :       ��ӡ������ģʽ����"<<endl;
			cout<<"   ����save()   :         �洢һ������ʽ"<<endl;
			cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
			cmd();
			system("cls");
			founctions_screen();
			break;
		}
		case 9:
		{
			system("cls");
			founctions_screen();
			break;
		}
		default:
		{
			cout<<"���������������������룡"<<endl;
			break;
		}
	}
	}
	loop();
}

void cmd()
{
	cout<<"@_@ ==> ";
	string in;
	getline(cin,in);
	DAS(in);
	if (in == "exit()") return;
	else if (in == "all()") print_all();
	else if (in == "save()")
	{
		if (sum >= max)
		{
			cout<<"�ֿ��������볢���������ܣ�"<<endl;
		} else {
			cout<<"��������Ҫ��ӵĶ���ʽ��"<<endl;
			string one_input;
			getline(cin,one_input);
			DAS(one_input);
			if (one_input.compare("0")==0) {write();exit(0);}
			if (one_input.compare("9")==0)
					{
						founctions_screen();
						loop();
						write();
						exit(0);
					}
			polynomial po_input;
			po_input.input(one_input);
			cout<<"������Ķ���ʽΪ��"<<endl;
			po_input.print();
			if (po_input.getName()!="\0")
			{
				repo[sum] = po_input;
				sum++;
			}
		}
	} else if (in == "help()") {
		cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
		cout<<"        ��������exit()�˳�������ģʽ"<<endl;
		cout<<"Ϊ������������������������ṩ0������9���ع��ܱ�"<<endl;
		cout<<"  Ҫ���ж���ʽ����ʱ���ȱ��棬�������ʾ����"<<endl;
		cout<<"   ����all()    :     ��ӡ���вֿ��еĶ���ʽ"<<endl;
		cout<<"   ����help()   :       ��ӡ������ģʽ����"<<endl;
		cout<<"   ����save()   :         �洢һ������ʽ"<<endl;
		cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
	} else {
		int opos;
		int find = 0;
		for (int i = 0; i < sum; i++)
		{
			if (repo[i].getName() == in)
			{
				find = 1;
				repo[i].print();
				break;
			}
		}
		if (!find)
		{
			if (in[0]=='('&&isR(0,in))
			{
				polynomial re;
				re.build(0,in);
				re.print();
			} else if ((opos = in.find("+"),opos!=in.npos)&&find_poly(in.substr(0,opos))!=-1&&find_poly(in.substr(opos+1))!=-1) {
				polynomial apo = repo[find_poly(in.substr(0,opos))].add(repo[find_poly(in.substr(opos+1))]);
				apo.print();
			} else if ((opos = in.find("-"),opos!=in.npos)&&find_poly(in.substr(0,opos))!=-1&&find_poly(in.substr(opos+1))!=-1) {
				polynomial apo = repo[find_poly(in.substr(0,opos))].subtract(repo[find_poly(in.substr(opos+1))]);
				apo.print();
			} else if ((opos = in.find("*"),opos!=in.npos)&&find_poly(in.substr(0,opos))!=-1&&find_poly(in.substr(opos+1))!=-1) {
				polynomial apo = repo[find_poly(in.substr(0,opos))].multiplication(repo[find_poly(in.substr(opos+1))]);
				apo.print();
			} else if ((opos = in.find("'"),opos!=in.npos)&&find_poly(in.substr(0,opos))!=-1&&in.find_last_not_of("'")==opos-1) {
				polynomial apo = repo[find_poly(in.substr(0,opos))].differentiation();
				for (int i = 1; i < in.length()-opos; i++) apo = apo.differentiation();
				apo.print();
			} else {
				if (in.length()) cout<<"����: ���������������"<<endl;
			}
		}
	}
	cmd();
}

void read()         // �ļ�������
{
	ifstream in("poly.txt");
	int i = 0;
	while (1)
	{
		in>>repo[i];
		if (!in) break;
		i++;
	}
	sum = i;
	in.close();
}

void write()        // �ļ�д����
{
	fclose(fopen("poly.txt", "w"));
	ofstream out("poly.txt");
	out.clear();
	while (sum--)
	{
		out<<repo[sum];
	}
	out.close();
}

void DAS(string& s)    // ɾ�����пո�
{
	int it;
	while (it = s.find(" "),it!=s.npos)
	{
		s.replace(it,1,"");
	}
}
