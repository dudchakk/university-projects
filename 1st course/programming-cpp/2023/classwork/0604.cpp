#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
  vector<int> vec = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  
  auto it = unique(vec.begin(), vec.end());
  vec.erase(it, vec.end());
  
  // Вектор vec буде мати наступний вигляд: {1, 2, 3, 4}
  
  for(auto i : vec)
  {
    cout << i << " ";
  }
}
