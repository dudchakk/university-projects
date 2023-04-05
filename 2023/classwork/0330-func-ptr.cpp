#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <math.h>

using namespace std;

string Tab(double(*f)(double), double a, double b, int n)
{
	ostringstream os;

	os << "|" << setw(5) << "x" << setw(5) << "|" << setw(5) << "f(x)" << setw(5) << "|" << endl;
	
	int h = (b - a) / n;
	for (a; a < n; a++)
	{
		os << "|" << setw(5) << a << setw(5) << "|" << setw(5) << f(a) << setw(5) << "|" << endl;
	}
	
	return os.str();
}

double f1(double x) 
{
	return pow(x, 3) + pow(x, 2) - 8 * x + 9;
}

int main()
{
	double a, b;
	int n;
	
	cout << "Enter a, b and number of points: " << endl;
	cin >> a;
	cin >> b;
	cin >> n;
	
	string st, st1, st2;
	
	st = Tab(sin, a, b, n);
	
	ofstream file("result.txt");
	file << "sin" << endl << st;
	st1 = Tab(f1, a,b,n);
	
	file << "x^3+x^2-8x+9" << endl << st1;
	st2 = Tab([](double x) {return sin(x) + 8 * tan(x) - 24 * pow(x, 2); }, 1, 3, 3);
	
	file << "sin(x)+8tg(x)-24x^2" << endl <<st2;	
	
	file.close();
	return 0;
}