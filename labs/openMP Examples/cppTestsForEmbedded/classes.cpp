#include<iostream>
using namespace std;

class C
{
	void f3(){}
	void f4(){}
};

class B
{
public:
	int s;
	static int r;
};
class Simple
{
public:
	int a,b;
	void fn(){}
};
int global;
inline void fn()
{
	int s=90;
	s++;
	s*=100;
	global+=s;
}

void main1()
{
	fn();
	fn();
	fn();
	Simple s;
	s.a=22;
	s.b=88;
	s.fn();
	Simple t;
	int r;
	r=20;
	Simple w;
	B p1,p2,p3,p4;
	cout << global;
	cout << sizeof(p1) << " " << &p1 << endl;;
	cout << sizeof(p2) << " " << &p2 << endl;;
	cout << sizeof(p3) << " " << &p3 << endl;;
	cout << sizeof(p4) << " " << &p4 << endl;;


}