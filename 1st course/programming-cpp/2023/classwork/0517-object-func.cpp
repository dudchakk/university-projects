#include <iostream>
#include <list>
#include <functional>
//#include <algorithm>
using namespace std;

template<class In, class T, class BinOp>

T acc(In first, In last, T init, BinOp op)
{
  for(auto i = first; i != last; ++i)
  {
	  init += op(*i);
  }
	
  return init;
}

template<class Type>

// Type mul(const Type& l, const Type& r)
// {
//   return l * r;
// }

struct mul //: public binary_function <T, T, T>
{
  int num;

  mul(int n): num(n) {}

  Type operator()(const Type& op) const
  {
    return op * num;
  }
};

int main()
{
  list<int> arr;
  string s = "1432"; //24
  for(auto i : s)
  {
    arr.push_back(int(i) - 48);
  }
  //for(auto i : arr) { cout << i << " "; }

  int sum = 0;
  sum = acc(arr.begin(), arr.end(), 0, mul<int>(2));
  cout << sum;
}
