#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

/* В текстовому файлі задано послідовність слів, розділених пропусками. Ввести слова в контейнер. 

Використовуючи алгоритми STL, кожне слово, яке починається і закінчується на одну і ту ж букву 
перемістити в інший контейнер. 

Утворити контейнер, який міститиме без повторів всі символи, що входять 
до складу даної послідовності слів. */

int main()
{
  ifstream file("words.txt");
  vector<string> arr;

  string str;
  while(getline(file, str))
  {
    istringstream ss(str);
    
    string word;
    while(ss >> word)
    {
      arr.push_back(word);
    }
  }

  vector<string> new_arr;
  
  copy_if(arr.begin(), arr.end(), back_inserter(new_arr), [](string s) { return s[0] == s[s.size() - 1]; });
  
  vector<char> letters;

  for(auto i : arr)
  {
    for(auto j : i)
    {
      if(!count(letters.begin(), letters.end(), j))
      {
        letters.push_back(j);
      }
    }
  }

  cout << "all letters: ";
  for(auto i : letters)
  {
    cout << i << " ";
  }

  cout << "\nnew array: ";
  for(auto i : new_arr)
  {
    cout << i << " ";
  }

  arr.erase(remove_if(arr.begin(), arr.end(), [](string s) { return s[0] == s[s.size() - 1]; }), arr.end());
  
  cout << "\narray, modified: ";
  for(auto i : arr)
  {
    cout << i << " ";
  }
}