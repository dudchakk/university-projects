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
  try
  {
    ofstream file("output2.txt");

    if(!file.is_open())
    {
      throw runtime_error("can't open file");
    }

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
        if(Greeting(UkrGreeting, name) != "З днем народження, " + name + "!")
        {
          throw ("invalid result");
        }
        break;
      case 2:
        file << Greeting(EngGreeting, name) << endl;
        if(Greeting(EngGreeting, name) != "Happy birthday, " + name + "!")
        {
          throw ("invalid result");
        }
        break;
      case 3:
        file << Greeting(GerGreeting, name) << endl;
        if(Greeting(GerGreeting, name) != "Alles Gute zum Geburtstag, " + name + "!")
        {
          throw ("invalid result");
        }
        break;
      case 4:
        file << Greeting(FrenchGreeting, name) << endl;
        if(Greeting(FrenchGreeting, name) != "Joyeux anniversaire, " + name + "!")
        {
          throw ("invalid result");
        }
        break;
      default:
        throw invalid_argument("bad argument: there is no such language in the list");
    }
  }

  catch(const invalid_argument &e)
  {
    cerr << e.what() << endl;
  }

  catch(const string &e)
  {
    cerr << e << endl;
  }

  catch(const runtime_error &e)
  {
    cerr << e.what() << endl;
  }
}