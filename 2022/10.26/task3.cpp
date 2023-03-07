#include <iostream>
#include <cmath>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

int main()
{
  double h, x, s, y;
  cout << "Enter a: ";
  cin  >> x;
  cout << "Enter h: ";
  cin  >> h;

  printf("X         S         y         Pohubka\n");

  double sprev, scur = 0;
  for(int i = 0; i < 10; i++, x += h)
  {
    int k = 0;
    s = 0;
    do 
    {
      sprev = scur;
      scur = 1.0 / (4 * k + 3) * pow(x, 4 * k + 3);
      s += scur;
      k++;
    } while(k < 2 || abs(sprev - scur) > 10e-5);

    double exp = (1 + x) / (1 - x);
    if(exp <= 0)
    {
      cout << "!! Cannot count log of a negative or zero number !!";
      break;
    }
    y = log(exp) / 4 - atan(x) / 2;
    double pohubka = abs((s - y) / y) * 100;
    printf("%10.5f%10.5f%10.5f%10.5f\n", x, s, y, pohubka);
  }
}