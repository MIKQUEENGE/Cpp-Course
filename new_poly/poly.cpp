#include <iostream>       
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

#define max 100
int sum = 0;
int stoi(string s);      	// 字符串转数字
int pow(int a, int b);		// a的b次方
void founctions_screen();
void loop();
void cmd();
void read();
void write();
void DAS(string&);      // delete add spaces删除所有空格

class polynomial		// 多项式类
{
private:
	string name;		// 多项式的名字，比如p
	int poly[max][2];
	int num;        
public:
	polynomial()       // 构造函数
	{
		for (int i = 0; i < max; i++) for (int j = 0; j < 2; j++) poly[i][j] = 0;
		num = 0;
		name = "\0";
	}
	polynomial(const polynomial &p)       // 拷贝函数
	{
		name = p.name;
		for (int i = 0; i < max; i++) for (int j = 0; j < 2; j++) poly[i][j] = p.poly[i][j];
		num = p.num;
	}
	~polynomial() {}                  // 析构函数
	int getNum() const
	{
		return num;
	}
	void setNum(const int n)
	{
		num = n;
	}
	void setName(const string s)           // 改名字
	{
		name = s;
	}
	string getName() const               // 获得名字
	{
		return name;
	}
	void input(string);             		// 用户输入
	void build(int, string);						// 把获取的信息传递到多项式中
	polynomial add(polynomial&);		// 加
	polynomial subtract(polynomial&);   // 减
	polynomial multiConstant(int);      // 乘常数
	int subsValue(int);                 // 代入常数
	polynomial multiplication(polynomial&);     // 乘
	int ifEqual(polynomial&);       // 判断相等
	polynomial differentiation();   // 求导
	void print();                   // 友好打印
	
	//运算符重载
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

polynomial repo[max];   // 用于存储多项式


int main()					 // 主函数
{
	read();
	founctions_screen();
	loop();
	write();
	return 0;
}



int stoi(string s)      // 字符串转数字
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



int pow(int a, int b)	// a的b次方
{
	int re = 1;
	for (int i = 1; i <= b; i++) re*=a;
	return re;
}

int isR(int pos, string a)            // 判断用户是否输入错误
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
				cout<<"您的输入的项过多！请确认输入的项数少于"<<max<<"!"<<endl;
				return 0;
			}
			if (i - m - 1 >= 10) {
				cout<<"您的数字大小超过范围！数字范围为-99999999~999999999"<<endl;
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
	for (int p = 0; p < i; p++)                 // 寻找并插入所有子项
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
				if (!have_print_nosort)   	// 打印未排序提示语
				{
					cout<<"您的输入未排序，系统已自动帮您排序！"<<endl;
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
					cout<<"您输入的部分项幂数相等，系统已帮您自动合并！"<<endl;
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

void polynomial::input(string a)             		// 用户输入
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
			cout<<"输入格式错误，请重新输入！"<<endl;
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
			cout<<"是否想保存此多项式，是请输入1，否请输入其他！"<<endl;
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
			if (ifName=="1")		// 对保存的多项式进行命名操作
			{
				cout<<"请命名:"<<endl;
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
						cout<<"名字必须以英文字母开头且只含有英文和数字！"<<endl;
						continue;
					} else {
						int nameR = 1;
						for (int i = 0; i < inName.length(); i++)
						{
							if ((inName[i]<'0'||inName[i]>'9')&&(inName[i]<'a'||inName[i]>'z')&&(inName[i]<'A'||inName[i]>'Z'))
							{
								cout<<"名字必须以英文字母开头且只含有英文和数字！"<<endl;
								nameR = 0;
								break;
							}
						}
						for (int i = 0; i < sum; i++)
						{
							if (repo[i].getName() == inName)
							{
								cout<<"该名称已被占用，请重新输入："<<endl;
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
			cout<<"名字必须以英文字母开头且只含有英文和数字！"<<endl;
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
					cout<<"输入格式错误，请重新输入！"<<endl;
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
				cout<<"输入格式错误，请重新输入！"<<endl;
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
						cout<<"该名称已被占用，请重新输入："<<endl;
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

polynomial polynomial::add(polynomial &addpoly)		// 加
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

polynomial polynomial::subtract(polynomial &subtpoly)   // 减
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

polynomial polynomial::multiConstant(int c)      // 乘常数
{
	polynomial re = *this;
	for (int i = 0; i < re.getNum(); i++)
	{
		re.poly[i][0] *= c;
	}
	return re;
}

int polynomial::subsValue(int v)                 // 代入常数
{
	int re = 0;
	for (int i = 0; i < num; i++)
	{
		re+=(poly[i][0]*(pow(v,poly[i][1])));
	}
	return re;
}

polynomial polynomial::multiplication(polynomial &multipoly)     // 乘
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

int polynomial::ifEqual(polynomial& epoly)       // 判断相等
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

polynomial polynomial::differentiation()   // 求导
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

void polynomial::print()                   // 友好打印
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

void founctions_screen()				// 打印功能表
{
	cout<<"-------------------------------\n";
	cout<<"|         多项式计算器        |\n";
	cout<<"-------------------------------\n";
	cout<<"\n";
	cout<<"*******************************\n";
	cout<<"*    ----  功能列表  ----     *\n";
	cout<<"*  1.      输入多项式         *\n";
	cout<<"*  2.     多项式加减乘        *\n";
	cout<<"*  3. 多项式与常数的乘法运算  *\n";
	cout<<"*  4.  求多项式代入某点的值   *\n";
	cout<<"*  5. 判断两个多项式是否相等  *\n";
	cout<<"*  6.  显示所有储存多项式     *\n";
	cout<<"*  7.   对某个多项式求导      *\n";
	cout<<"*  8.    进入命令行模式       *\n";
	cout<<"*  9.  帮助(查看功能列表)     *\n";
	cout<<"*  0.       退出系统          *\n";
	cout<<"*******************************\n";
}

void print_all()
{
	if (sum == 0)
	{
		cout<<"没有已存储的多项式！";
	} else {
		cout<<"目前已存储："<<sum<<"个多项式："<<endl;
		for (int i = 0; i < sum; i++)
		{
			repo[i].print();
		}
	}
}

int find_poly(string n)                  			// 在仓库中寻找多项式
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
	cout<<"是否想保存此多项式，是请输入1，否请输入其他！"<<endl;
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
	if (ifName=="1")		// 对保存的多项式进行命名操作
	{
		cout<<"请命名:"<<endl;
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
				cout<<"名字必须以英文字母开头且只含有英文和数字！"<<endl;
				continue;
			} else {
				int nameR = 1;
				for (int i = 0; i < inName.length(); i++)
				{
					if ((inName[i]<'0'||inName[i]>'9')&&(inName[i]<'a'||inName[i]>'z')&&(inName[i]<'A'||inName[i]>'Z'))
					{
						cout<<"名字必须以英文字母开头且只含有英文和数字！"<<endl;
						nameR = 0;
						break;
					}
				}
				for (int i = 0; i < sum; i++)
				{
					if (repo[i].getName() == inName)
					{
						cout<<"该名称已被占用，请重新输入："<<endl;
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
	cout<<"请选择主功能："<<endl;
	string client_input;
	getline(cin, client_input);
	DAS(client_input);
	if (client_input.length()!=1 || client_input[0]<'0' || client_input[0]>'9')
	{
		cout<<"您的输入有误，请重新输入！"<<endl;
	} else {
	int c = client_input[0]-'0';
	if (c == 0) return;
	switch(c)
	{
		case 1:
		{
			if (sum >= max)
			{
				cout<<"仓库已满，请尝试其他功能！"<<endl;
				break;
			}
			cout<<"请输入您要添加的多项式："<<endl;
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
			cout<<"您输入的多项式为："<<endl;
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
				cout<<"请选择："<<endl;
				cout<<"1. 加    2. 减   3. 乘"<<endl;
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
					cout<<"请输入第一个多项式："<<endl;
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
								cout<<"对不起，无法保存!库存已满！"<<endl;
							} else {
								repo[sum] = add_x;
								sum++;
							}
						}
					} else {
						int pos = find_poly(add_a);
						if (pos<0)
						{
							cout<<"多项式不存在！请重试！"<<endl;
							continue;
						} else {
							add_x = repo[pos];
						}
					}
					cout<<"请输入第二个多项式："<<endl;
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
								cout<<"对不起，无法保存!库存已满！"<<endl;
							} else {
								repo[sum] = add_y;
								sum++;
							}
						}
					} else {
						int pos = find_poly(add_b);
						if (pos<0)
						{
							cout<<"多项式不存在！请重试！"<<endl;
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
							cout<<"对不起，无法保存!库存已满！"<<endl;
						} else {
							repo[sum] = add_re;
							sum++;
						}
					}
					cout<<"两个多项式的和为："<<endl;
					add_re.print();
					break;
				} else if (one_input == "2") {
					cout<<"请输入被减数："<<endl;
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
								cout<<"对不起，无法保存!库存已满！"<<endl;
							} else {
								repo[sum] = add_x;
								sum++;
							}
						}
					} else {
						int pos = find_poly(add_a);
						if (pos<0)
						{
							cout<<"多项式不存在！请重试！"<<endl;
							continue;
						} else {
							add_x = repo[pos];
						}
					}
					cout<<"请输入减数："<<endl;
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
								cout<<"对不起，无法保存!库存已满！"<<endl;
							} else {
								repo[sum] = add_y;
								sum++;
							}
						}
					} else {
						int pos = find_poly(add_b);
						if (pos<0)
						{
							cout<<"多项式不存在！请重试！"<<endl;
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
							cout<<"对不起，无法保存!库存已满！"<<endl;
						} else {
							repo[sum] = add_re;
							sum++;
						}
					}
					cout<<"两个多项式的差为："<<endl;
					add_re.print();
					break;
				} else if (one_input == "3") {
					cout<<"请输入第一个多项式："<<endl;
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
								cout<<"对不起，无法保存!库存已满！"<<endl;
							} else {
								repo[sum] = add_x;
								sum++;
							}
						}
					} else {
						int pos = find_poly(add_a);
						if (pos<0)
						{
							cout<<"多项式不存在！请重试！"<<endl;
							continue;
						} else {
							add_x = repo[pos];
						}
					}
					cout<<"请输入第二个多项式："<<endl;
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
								cout<<"对不起，无法保存!库存已满！"<<endl;
							} else {
								repo[sum] = add_y;
								sum++;
							}
						}
					} else {
						int pos = find_poly(add_b);
						if (pos<0)
						{
							cout<<"多项式不存在！请重试！"<<endl;
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
							cout<<"对不起，无法保存!库存已满！"<<endl;
						} else {
							repo[sum] = add_re;
							sum++;
						}
					}
					cout<<"两个多项式的积为："<<endl;
					add_re.print();
					break;
				} else {
					cout<<"没有您输入的选项！请重新输入！"<<endl;
				}
			}
			break;
		}
		case 3:
		{
			cout<<"请输入多项式："<<endl;
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
						cout<<"对不起，无法保存!库存已满！"<<endl;
					} else {
						repo[sum] = add_x;
						sum++;
					}
				}
			} else {
				int pos = find_poly(add_a);
				if (pos<0)
				{
					cout<<"多项式不存在！请重试！"<<endl;
					break;
				} else {
					add_x = repo[pos];
				}
			}
			cout<<"请输入常数："<<endl;
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
					cout<<"您输入的不是整数，请重试！"<<endl;
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
					cout<<"对不起，无法保存!库存已满！"<<endl;
				} else {
					repo[sum] = add_re;
					sum++;
				}
			}
			cout<<"积为："<<endl;
			add_re.print();
			break;
		}
		case 4:
		{
			cout<<"请输入多项式："<<endl;
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
						cout<<"对不起，无法保存!库存已满！"<<endl;
					} else {
						repo[sum] = add_x;
						sum++;
					}
				}
			} else {
				int pos = find_poly(add_a);
				if (pos<0)
				{
					cout<<"多项式不存在！请重试！"<<endl;
					break;
				} else {
					add_x = repo[pos];
				}
			}
			cout<<"请输入常数："<<endl;
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
					cout<<"您输入的不是整数，请重试！"<<endl;
					b_isR = 0;
					break;
				}
			}
			if (!b_isR) break;
			int c = stoi(add_b);
			int add_re;			
			add_re = add_x.subsValue(c);
			cout<<"结果为："<<add_re<<endl;
			break;
		}
		case 5:
		{
			cout<<"请输入第一个多项式："<<endl;
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
						cout<<"对不起，无法保存!库存已满！"<<endl;
					} else {
						repo[sum] = add_x;
						sum++;
					}
				}
			} else {
				int pos = find_poly(add_a);
				if (pos<0)
				{
					cout<<"多项式不存在！请重试！"<<endl;
					break;
				} else {
					add_x = repo[pos];
				}
			}
			cout<<"请输入第二个多项式："<<endl;
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
						cout<<"对不起，无法保存!库存已满！"<<endl;
					} else {
						repo[sum] = add_y;
						sum++;
					}
				}
			} else {
				int pos = find_poly(add_b);
				if (pos<0)
				{
					cout<<"多项式不存在！请重试！"<<endl;
					break;
				} else {
					add_y = repo[pos];
				}
			}
			int add_re;
			add_re = add_x.ifEqual(add_y);
			if (add_re) cout<<"相等"<<endl;
			else cout<<"不等"<<endl;
			break;
		}
		case 6:
		{
			print_all();
			break;
		}
		case 7:
		{
			cout<<"请输入要求导的多项式："<<endl;
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
						cout<<"对不起，无法保存!库存已满！"<<endl;
					} else {
						repo[sum] = add_x;
						sum++;
					}
				}
			} else {
				int pos = find_poly(add_a);
				if (pos<0)
				{
					cout<<"多项式不存在！请重试！"<<endl;
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
					cout<<"对不起，无法保存!库存已满！"<<endl;
				} else {
					repo[sum] = add_re;
					sum++;
				}
			}
			cout<<"求导后为："<<endl;
			add_re.print();
			break;
		}
		case 8:
		{
			system("cls");
			cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
			cout<<"  进入命令行模式，可以输入exit()退出命令行模式"<<endl;
			cout<<"为了提高命令行体验质量，不提供0结束与9返回功能表"<<endl;
			cout<<"  要进行多项式运算时请先保存，否则会提示错误！"<<endl;
			cout<<"   输入all()    :     打印所有仓库中的多项式"<<endl;
			cout<<"   输入help()   :       打印命令行模式帮助"<<endl;
			cout<<"   输入save()   :         存储一个多项式"<<endl;
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
			cout<<"您的输入有误，请重新输入！"<<endl;
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
			cout<<"仓库已满，请尝试其他功能！"<<endl;
		} else {
			cout<<"请输入您要添加的多项式："<<endl;
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
			cout<<"您输入的多项式为："<<endl;
			po_input.print();
			if (po_input.getName()!="\0")
			{
				repo[sum] = po_input;
				sum++;
			}
		}
	} else if (in == "help()") {
		cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
		cout<<"        可以输入exit()退出命令行模式"<<endl;
		cout<<"为了提高命令行体验质量，不提供0结束与9返回功能表"<<endl;
		cout<<"  要进行多项式运算时请先保存，否则会提示错误！"<<endl;
		cout<<"   输入all()    :     打印所有仓库中的多项式"<<endl;
		cout<<"   输入help()   :       打印命令行模式帮助"<<endl;
		cout<<"   输入save()   :         存储一个多项式"<<endl;
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
				if (in.length()) cout<<"错误: 不存在这样的命令！"<<endl;
			}
		}
	}
	cmd();
}

void read()         // 文件读函数
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

void write()        // 文件写函数
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

void DAS(string& s)    // 删除所有空格
{
	int it;
	while (it = s.find(" "),it!=s.npos)
	{
		s.replace(it,1,"");
	}
}
