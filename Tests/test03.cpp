#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	double base;
	base = 2;
	double e1;
	cin >> e1;
	double e2;
	cin >> e2;
	double e3;
	cin >> e3;
	double result;
	result = ((1+pow(base,pow(e1,pow(e2,e3))))-1);
	cout << result;
	cout << "\n";
}
