#include <iostream>
#include <string>
using namespace std;

int main()
{
  int a, b, c;
  cout << "Enter number 1:" << endl;
  cin  >> a;
  cout << "Enter number 2:" << endl;
  cin  >> b;
  cout << "Enter number 3:" << endl;
  cin  >> c;

  int min, max;
  min = a < b ? a : b;
  min = min < c ? min : c;
  max = a > b ? a : b;
  max = max > c ? max : c;
  
  if(min < 24 && max < 60)
    cout << "The answer is yes" << endl;
  else
    cout << "The answer is no" << endl;
  return 0;
}