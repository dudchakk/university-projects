#include <iostream>
#include <fstream>

using namespace std;

string Greeting(string(*f)(string), string name)
{
  return f(name);
}

string UkrGreeting(string name)
{
  return "З днем народження, " + name + "!";
}

string EngGreeting(string name)
{
  return "Happy birthday, " + name + "!";
}

string GerGreeting(string name)
{
  return "Alles Gute zum Geburtstag, " + name + "!";
}

string FrenchGreeting(string name)
{
  return "Joyeux anniversaire, " + name + "!";
}

int main()
{
  ofstream file("output2.txt");

  cout << "Enter your name: ";
  string name;
  cin >> name;

  cout << endl << "Choose language:" << endl;
  cout << "1 - ukraininan" << endl;
  cout << "2 - english" << endl;
  cout << "3 - german" << endl;
  cout << "4 - french" << endl;
  int lang;
  cin >> lang;

  switch(lang)
  {
    case 1:
      file << Greeting(UkrGreeting, name) << endl;
      break;
    case 2:
      file << Greeting(EngGreeting, name) << endl;
      break;
    case 3:
      file << Greeting(GerGreeting, name) << endl;
      break;
    case 4:
      file << Greeting(FrenchGreeting, name) << endl;
      break;
    default:
      cout << "Invalid language";
  }
}