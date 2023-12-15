#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* а) Дана функція f повинна замінити в контейнері l всі числа, що лежать в діапазоні [a,b] на 
своє значення в степені 3. 
Дописати який саме <Алгоритм> треба використати і визначити необхідний функціональний об`єкт Fun, 
який використовується у вказаному алгоритмі для  виконання завдання.

void f(vector<double> l, double a, double b )
{
  //Task А       
  <Алгоритм>(l.begin(),l.end(),Fun(a,b));
  //Task Б
} */

/* Б) Використовуючи алгоритми STL ,дописати функцію так: 
- змінений контейнер посортувати у незростаючому порядку
- Порахувати кількість нулів в контейнері
- Вивести результати у потік. */

struct Fun
{
  double a;
  double b;
  
  Fun(double aa, double bb): a(aa), b(bb) {}
  
  double operator()(double x)
  {
    if(x >= a && x <= b)
    {
      x = x * x * x;
    }
    return x;
  }
};

int f(vector<double>& l, double a, double b)
{
  transform(l.begin(), l.end(), l.begin(), Fun(a, b));

  sort(l.rbegin(), l.rend());

  int zero_cnt = 0;
  for(int i : l)
  {
    while(i > 0)
    {
      int tmp = i % 10;
      if(tmp == 0)
      {
        zero_cnt++;
      }
      i /= 10;
    }
  }
  return zero_cnt;
}

int main()
{
  vector<double> arr = { 1, 2, 3, 10, 101};
  
  int zero_cnt = f(arr, 2, 10);

  for(auto i : arr)
  {
    cout << i << " ";
  }
  cout << "\n";
  cout << "number of zeros: " << zero_cnt;
}