#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int main()
{
  float R;
  cout << "Enter radius:" << endl;
  cin  >> R;
  cout << "Length = " << 2.0 * 3.14 * R << endl;
  cout << "Square = " << 3.14 * R * R << endl;
  cout << "Volume = " << 4.0 / 3.0 * 3.14 * R * R * R << endl;
  return 0;
}