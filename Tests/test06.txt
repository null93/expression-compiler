#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	double e1;
	cin >> e1;
	double e2;
	cin >> e2;
	double e3;
	cin >> e3;
	double result;
	result = ((1+pow(2,pow(e1,pow(e2,e3))))-1);
	cout << result;
	cout << "\n";
	double a;
	a = 1.5;
	double b;
	b = 2;
	double c;
	c = 100.0;
	double d;
	d = 0.001;
	a = ((((((a*b)*c)*d)+a)-b)+((c/d)*pow(a,2)));
	cout << a;
	cout << "\n";
}
