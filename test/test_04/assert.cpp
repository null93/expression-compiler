#include <iostream>
#include <cmath>

using namespace std;

int main()
{
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
