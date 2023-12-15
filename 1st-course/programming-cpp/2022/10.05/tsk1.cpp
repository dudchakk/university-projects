#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int main()
{
  int k;
  cout << "Enter k:" << endl;
  cin  >> k;
  cout << "Hour count = " << k / 3600 << endl;
  k %= 3600;
  cout << "Minute count = " << k / 60 << endl;
  k %= 60;
  cout << "Second count = " << k << endl;
  return 0;
}