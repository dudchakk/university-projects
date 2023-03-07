#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class AcDisc
{
  private:
    string name;
    bool control; //0 - екзамен, 1 - залік

  public:
    AcDisc(): name(""), control(0) {}
    AcDisc(string n, bool c): name(n), control(c) {}
    AcDisc(const AcDisc &ad): name(ad.name), control(ad.control) {}

    friend istream &operator>>(istream &is, AcDisc &ad)
    {
      cout << "Enter discipline's name: " << endl;
      is >> ad.name;
      cout << "Enter 0, if discipline's control is exam, and 1, if test: " << endl;
      is >> ad.control;
      cout << "-----" << endl;

      return is;
    }
    friend ostream &operator<<(ostream &os, AcDisc &ad)
    {
      os << "Discipline's name is " << ad.name << endl;
      os << "Discipline's control is " << ad.control << endl;
      os << "-----" << endl;

      return os;
    }

    bool operator>(const AcDisc& ad2)
    {
      return name > ad2.name;
    }
    bool getControl() const
    {
      return control;
    }
    string getName() const
    {
      return name;
    }
    void setControl(bool c)
    {
      control = c;
    }

};

void sort(AcDisc* array, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = i + 1; j < n; j++)
		{
			if(array[i] > array[j])
			{
				AcDisc temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}

int main()
{
  int n1 = 6, n2 = 3;
  AcDisc arr[n1];
  for(int i = 0; i < n2; i++)
  {
    cout << "Enter discipline " << i + 1 << " information: " << endl;
    cin >> arr[i];
  }
  arr[3];
  AcDisc a1("n", 0);
  arr[4] = a1;
  arr[5] = arr[2];

  sort(arr, n1);
  // for(int i = 0; i < n1; i++)
  //   cout << arr[i];

  int ec = 0;
  for(int i = 0; i < n1; i++)
  {
    if(!arr[i].getControl())
      ec++;
  }
  cout << endl;
  //cout << "Disciplines: exam - " << ec << ", test - " << n1 - ec << endl;

  string n;
  bool f = true;
  cout << "Enter name: " << endl;
  cin >> n;
  for(int i = 0; i < n1; i++)
  {
    if(arr[i].getName() == n)
    {
      arr[i].setControl(1);
      f = false;
    }
  }
  if(f)
    cout << "There is no such discipline" << endl;
  for(int i = 0; i < n1; i++)
    cout << arr[i] << endl;
}