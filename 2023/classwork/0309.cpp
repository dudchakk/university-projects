#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

/* Визначити базовий тип 
«Компʼютер»
- фірма
- ціна
Визначити 2 похідні від нього типи: 
«стаціонарний»
- тип: ігровий, офісний
- процесор
«ноутбук»
- діагональ
- памʼять

У текстовому файлі задано дані про 5 компʼютерів. Зчитати ці дані в один масив  і вивести у текстовий файл:
1)всі компʼютери, посортовані за ціною, 
2)обчислити загальну вартість всіх ноутбуків; 
3) за вказаною фірмою вивести всі стаціонарні компʼютери */

class Computer
{
  protected:
    string firm_;
    int price_;

  public:
    virtual void input(istream &is)
    {
      is >> firm_ >> price_;
    }

    friend istream &operator>>(istream &is, Computer &t)
    {
      t.input(is);
      return is;
    }

    virtual void output(ostream &os)
    {
      os << "firm: " << firm_ << ", price: " << price_;
    }

    friend ostream &operator<<(ostream &os, Computer &t)
    {
      t.output(os);
      return os;
    }

    bool operator<(const Computer &t)
    {
      return price_ < t.price_;
    }

    int getPrice() { return price_; }

    string getFirm() { return firm_; }

    virtual char getType() { return ' '; }
};

class Stationary : public Computer
{
  private:
    bool type_; // 0 - gaming, 1 - office
    string proc_;

  public:
    void input(istream &is)
    {
      Computer::input(is);
      is >> type_ >> proc_;
    }

    void output(ostream &os)
    {
      Computer::output(os);
      os << ", type: " << (type_ == 0 ? "gaming" : "office") << ", processor: " << proc_ << endl;
    }

    char getType() { return 's'; }
};

class Laptop : public Computer
{
  private:
    float diag_;
    int mem_;

  public:
    void input(istream &is)
    {
      Computer::input(is);
      is >> diag_ >> mem_;
    }

    void output(ostream &os)
    {
      Computer::output(os);
      os << ", diagonal: " << diag_ << ", memory: " << mem_ << endl;
    }

    char getType() { return 'l'; }
};

int main()
{
  string firm;
  cout << "Enter firm: ";
  cin >> firm; 
  
  vector<Computer*> arr;
  ifstream file1("input.txt");
  ofstream file2("output.txt");

  int sum = 0;

  while(!file1.eof())
  {
    Computer* temp;
    int n;
    file1 >> n;

    if(n == 1)
      temp = new Stationary();
    else
    if(n == 2)
      temp = new Laptop();
    
    temp->input(file1);
    arr.push_back(temp);
    sum += temp->getPrice();
  }
  
  sort(arr.begin(), arr.end(), [](Computer* c1, Computer* c2) { return *c1 < *c2; });

  file2 << "All phones, sorted by price:" << endl;
  
  for(int i = 0; i < arr.size(); i++)
    arr[i]->output(file2);
  
  file2 << endl << "Total price: " << sum << endl << endl;

  bool check = false;
  file2 << "Stationary computers from the " << firm << ":" << endl;
  
  for(int i = 0; i < arr.size(); i++)
  {
    if(arr[i]->getType() == 's' && arr[i]->getFirm() == firm)
    {
      arr[i]->output(file2);
      check = true;
    }
  }

  if(!check)
    file2 << "No computers from this firm" << endl;

  file1.close();
  file2.close();
}