#include <iostream>
#include <string>
#include <math.h>
#include <cmath>
using namespace std;

int main()
{
  float x;
  cout << "Enter x:" << endl;
  cin  >> x;
  cout << pow(pow(x, 8) + pow(8, x), 1/8.0) << endl;
  return 0;
}