#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <cmath>
using namespace std;

int main()
{
  int a, b;
  cout << "Enter number1:" << endl;
  cin  >> a;
  cout << "Enter number2:" << endl;
  cin  >> b;
  cout << "AVG arithmetic = " << float(a + b) / float(2) << endl;
  cout << "AVG geometric = " << sqrt(a * b) << endl;
  return 0;
}