#include <iostream>
#include <cmath>
using namespace std;

/*
Визначити функцію, skor(a,b,q,p) від цілих параметрів (b != 0) , що приводить  дріб a/b до нескоротного виду p/q . Використати її для приведення дробу 1+1/2+1/3+…+1/20 до нескоротного виду c/d.
*/
#define int64 long long

void skor(int64 a, int64 b, int64 &p, int64 &q)
{
  if(b == 0)
  {
    cout << "Invalid number b!!" << endl;
    return;
  }

  int64 min = a > b ? b : a;
  min = sqrt(min);
  for(int64 div = 2; div <= min; div++)
    if(a % div == 0 && b % div == 0)
    {
      a /= div;
      b /= div;
      div--;
      min = a > b ? b : a;
      min = sqrt(min);
    }
  p = a;
  q = b;
}

int main()
{
  int64 a = 0, b = 1, p, q;
  
  for(int i = 2; i <= 20; i++)
    b *= i;
  for(int i = 1; i <= 20; i++)
    a += b / i;

  skor(a, b, p, q);
  cout << p << " / " << q << " = " << 1.0 * p / q << endl;
}