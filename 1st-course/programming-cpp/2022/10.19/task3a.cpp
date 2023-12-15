#include <iostream>
using namespace std;

int main()
{
  double x_imin2 = 0.0;
  double x_min1 = 5.0/8;
  double x;
  cout << x_imin2 << endl << x_min1 << endl;

  for(int i = 3; i <= 20; i++)
  {
    x = x_min1 / 2.0 + 3 * x_imin2 / 4.0;
    cout << x << endl;
    x_imin2 = x_min1;
    x_min1 = x;
  }
}