#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Person
{
  protected:
    string name_;
    int age_;
    //int income_;
  
  public:
    virtual void input(istream &is)
    {
      cin >> name_;
      cin >> age_;
      //cin >> income_;
    }
    virtual void print(ostream &os)
    {
      os << name_ << ", " << age_ << endl;
    }
    virtual int getIncome() = 0;
};

class Student : public Person
{
  private:
    string group_;
    int wage_;
  
  public:
    void input(istream &is)
    {
      Person::input(is);
      is >> group_;
      is >> wage_;
    }
    void input(istream &is)
    {
      Person::input(is);
      
    }
    int getIncome() { return wage_; }
};

class Worker : public Person
{
  private:
    int income_;
  
  public:
    void input(istream &is)
    {
      Person::input(is);
      is >> income_;
    }
    int getIncome() { return income_; }
};

int main()
{
  ifstream file("data.txt");
  vector<Person*> list;
  int size = 0;

  while(file.eof())
  {
    int n;
    Person* p;
    file >> n;
    if(n == 1)
      p = new Student();
    else
    if(n == 2)
      p = new Worker();
    p->input(file);
    list.push_back(p);
  }
}