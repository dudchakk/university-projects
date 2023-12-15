#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

string Modified(double(*f)(double), double* a, int n)
{
  ostringstream oss;

  oss << fixed << setprecision(2);

  int wth = 10;
  for(int i = 0; i < n; i++)
  {
    oss << "| " << setw(wth) << i << " | " << setw(wth) << a[i] << " | " << setw(wth) << f(a[i]) << " |";
    oss << endl;
  }
  
  return oss.str();
}

double Square(double n)
{
  return pow(n, 2);
}

double Trigonometric(double n)
{
  return sin(n) + cos(n) - tan(n);
}

double Round(double n)
{
  return round(n);
}

int main()
{
  ofstream file("output1.txt");

  int n = 4;
  double arr[] = { 1.1, 2.3, 5.8, 13.6 };

  file << "Square:" << endl;
  file << Modified(Square, arr, n);

  file << endl << "Expression sin + cos - tg:" << endl;
  file << Modified(Trigonometric, arr, n);

  file << endl << "Round:" << endl;
  file << Modified(Round, arr, n);

  file.close();
}