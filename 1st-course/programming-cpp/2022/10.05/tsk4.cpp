#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int main()
{
  int k;
  cout << "Enter number:" << endl;
  cin  >> k;
  if(k % 7 == 0)
    cout << 7 << endl;
  else
    cout << k % 7 << endl;
  return 0;
}