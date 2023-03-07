#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

/* Визначити абстрактний тип: 
телефон:
- назва
- фірма
- ціна
Визначити 2 похідні від нього типи:
мобільний телефон
- колір
- об’єм пам’яті
радіотелефон
- радіус дії
- наявність автовідповідача

У двох текстових файлах задано дані про телефони двох різних фірм. Зчитати ці дані в один масив і 
вивести у текстовий файл: 
1) всі телефони, посортовані за ціною із зазначенням загальної суми;
2) радіотелефони з автовідповідачем */

class Telephone
{
  protected:
    string name_;
    string firm_;
    int price_;

  public:
    Telephone(): name_(""), firm_(""), price_(0) {}
    Telephone(string n, string f, float p): name_(n), firm_(f), price_(p) {}

    virtual void input(istream &is)
    {
      is >> name_;
      is >> firm_ >> price_;
    }

    friend istream &operator>>(istream &is, Telephone &t)
    {
      t.input(is);
      return is;
    }

    virtual void output(ostream &os)
    {
      os << "name: " << name_ << ", firm: " << firm_ << ", price: " << price_;
    }

    friend ostream &operator<<(ostream &os, Telephone &t)
    {
      t.output(os);
      return os;
    }

    bool operator<(const Telephone &t)
    {
      return price_ < t.price_;
    }

    int getPrice() { return price_; }

    virtual int isAutoAnswer() { return -1; }
};

class MobPhone : public Telephone
{
  protected:
    string color_;
    int mem_sz_;

  public:
    void input(istream &is)
    {
      Telephone::input(is);
      is >> color_ >> mem_sz_;
    }

    void output(ostream &os)
    {
      Telephone::output(os);
      os << ", color: " << color_ << ", memory size: " << mem_sz_ << endl;
    }
};

class RadioPhone : public Telephone
{
  protected:
    int act_rad_;
    bool auto_ans_;

  public:
    void input(istream &is)
    {
      Telephone::input(is);
      is >> act_rad_ >> auto_ans_;
    }

    void output(ostream &os)
    {
      Telephone::output(os);
      os << ", active radius: " << act_rad_ << ", is auto answer: " << auto_ans_ << endl;
    }

    int isAutoAnswer() { return auto_ans_; }
};

int main()
{
  vector<Telephone*> arr;
  ifstream file1("input1.txt");
  ofstream file2("output1.txt");

  int sum = 0;

  while(!file1.eof())
  {
    Telephone* temp;
    int n;
    file1 >> n;

    if(n == 1)
      temp = new MobPhone();
    else
    if(n == 2)
      temp = new RadioPhone();
    
    temp->input(file1);
    arr.push_back(temp);
    sum += temp->getPrice();
  }
  
  sort(arr.begin(), arr.end(), [](Telephone* t1, Telephone* t2) { return *t1 < *t2; });

  file2 << "All phones, sorted by price:" << endl;
  for(int i = 0; i < arr.size(); i++)
    arr[i]->output(file2);
  file2 << "Total sum: " << sum << endl << endl;

  file2 << "Radio phones with auto answer:" << endl;
  for(int i = 0; i < arr.size(); i++)
  {
    if(arr[i]->isAutoAnswer() == 1)
      arr[i]->output(file2);
  }

  file1.close();
  file2.close();
}