#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//3.	Ввести текст, що складається зі слів, розділених пропуском. В кінці тексту – крапка. Для кожного слова визначити яка частка в ньому голосних букв. (по відношенню до всіх інших букв у слові, напр. abhiho = 50%) .

int main()
{
  string text;
  cout << "Enter text: " << endl;
  getline(cin, text);

  int n = text.length();
  for(int i = 0; i < n; i++)
    if(text[i] >= 'A' && text[i] <= 'Z')
      text[i] = tolower(text[i]);

  int vowelC = 0, allC = 0, wordI = 1;
  for(int i = 0; i < n; i++)
  {
    if(text[i] == ' ' || text[i] == '.')
    {
      cout << "word " << wordI << ": " << (1.0 * vowelC / allC) * 100 << '%' << endl;
      vowelC = 0;
      allC = 0;
      wordI++;
    }
    else
    {
      allC++;
      if(text[i] == 'a' || text[i] == 'e' || text[i] == 'i' || text[i] == 'o' || text[i] == 'u' || text[i] == 'y')
        vowelC++;
    }
  }
}