#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

/* Для розв'язування задачі використовувати контейнер list.

Ввести послідовність символів.
- Видалити з неї всі коми, що йдуть перед першою крапкою
- замінити всі цифри 3, що йдуть після першої крапки, на знак +. */

int main()
{
  try 
  {
    list<char> str_list;
    list<char>::iterator i;

    string s;
    cout << "Enter char sequence: ";
    cin >> s;
    
    for(size_t i = 0; i < s.length(); i++)
    {
      str_list.push_back(s[i]);
    }

    list<char>::iterator dot = find(str_list.begin(), str_list.end(), '.');
    if(dot == str_list.end())
    {
      throw invalid_argument("Sequence must have a dot");
    }
    
    for(i = str_list.begin(); i != dot; i++)
    {
      if(*i == ',')
      {
        i = str_list.erase(i);
        i--;
      }
    }

    replace(dot, str_list.end(), '3', '+');

    for(i = str_list.begin(); i != str_list.end(); i++)
    {
      cout << *i;
    }
  }

  catch(invalid_argument &e)
  {
    cerr << e.what() << "\n";
  }
}