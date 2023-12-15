#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

/* Визначити: 
тип «Шпаргалка»:
- предмет
- номер
та похідні від нього типи:
«Паперова»:
- розмір
- місце переховування
та «Електронна»:
- назва носія
Визначити тип «Студент»:
- ПІП
- група
- масив шпаргалок

В текстовому файлі задано дані про n студентів. Зчитати ці дані у масив і:
1) видрукувати у текстовий файл список всіх шпаргалок, посортованих за предметом та номерами. 
2) В інший текстовий файл вивести всі електронні шпаргалки на носіях «комп» та їх кількість. */

enum CheatSheetTypes
{
  kPaperCS = 1,
  kElectronicCS = 2
};

class CheatSheet
{
  protected:
    string subject_;
    int num_;
  
  public:
    virtual void input(istream &is)
    {
      is >> subject_ >> num_;
    }

    friend istream &operator>>(istream &is, CheatSheet &c)
    {
      c.input(is);
      return is;
    }

    virtual void output(ostream &os)
    {
      os << "subject: " << subject_ << ", number: " << num_;
    }

    friend ostream &operator<<(ostream &os, CheatSheet &c)
    {
      c.output(os);
      return os;
    }

    string getSubject() { return subject_; }
    int getNum() { return num_; }

    virtual string getCarrierName() { return "-1"; }
};

class PaperCS : public CheatSheet
{
  int size_;
  string hid_plc_;

  public:
    void input(istream &is)
    {
      CheatSheet::input(is);
      is >> size_ >> hid_plc_;
    }

    void output(ostream &os)
    {
      CheatSheet::output(os);
      os << ", size: " << size_ << ", hide place: " << hid_plc_ << endl;
    }    
};

class ElectronicCS : public CheatSheet
{
  string cr_name_;

  public:
    void input(istream &is)
    {
      CheatSheet::input(is);
      is >> cr_name_;
    }

    void output(ostream &os)
    {
      CheatSheet::output(os);
      os << ", carrier name: " << cr_name_ << endl;
    }

    string getCarrierName() { return cr_name_; }
};

class Student
{
  string name_;
  string grp_;
  vector<CheatSheet*> cs_arr_;

  public:
    Student(): name_(""), grp_("") {}
    
    friend istream &operator>>(istream &is, Student &s)
    {
      string t1, t2, t3;
      is >> t1 >> t2 >> t3;
      s.name_ = t1 + " " + t2 + " " + t3;
      is >> s.grp_;

      size_t n;
      is >> n;

      for(int i = 0; i < n; i++)
      {
        size_t type;
        is >> type;

        switch(type)
        {
          case kPaperCS:
            s.cs_arr_.push_back(new PaperCS());
            s.cs_arr_.back()->input(is);
            break;
          case kElectronicCS:
            s.cs_arr_.push_back(new ElectronicCS());
            s.cs_arr_.back()->input(is);
            break;
        }
      }
      return is;
    }

    friend ostream &operator<<(ostream &os, Student &s)
    {
      os << "full name: " << s.name_ << ", group: " << s.grp_ << ", cheat sheets: " << endl;
      for(size_t i = 0; i < s.cs_arr_.size(); i++)
        os << *(s.cs_arr_[i]);
      return os;
    }

    size_t GetSCCount() { return cs_arr_.size(); }
    CheatSheet* GetSCByIndex(size_t index) { return cs_arr_[index]; }
};

bool CSComparer(CheatSheet *x, CheatSheet *y) 
{
  if(x->getSubject() == y->getSubject())
    return x->getNum() < y->getNum();
  else
    return x->getSubject() < y->getSubject();
}

int main()
{
  vector<Student> arr;

  ifstream file1("input2.txt");
  ofstream file2("output2_all_sorted.txt");
  ofstream file3("output2_elec_only.txt");

  while(!file1.eof())
  {
    arr.push_back(*(new Student()));
    file1 >> arr.back();
  }

  vector<CheatSheet*> cs_arr;

  for(int i = 0; i < arr.size(); i++)
    for(int j = 0; j < arr[i].GetSCCount(); j++)
      cs_arr.push_back(arr[i].GetSCByIndex(j));

  sort(cs_arr.begin(), cs_arr.end(), CSComparer);

  int n = 0;

  for(int i = 0; i < cs_arr.size(); i++)
  {
    file2 << *(cs_arr[i]);

    if(cs_arr[i]->getCarrierName() == "comp")
    {
      n++;
      file3 << *(cs_arr[i]);
    }
  }
  file3 << endl << "Number of electronic cheat sheets: " << n;

  file1.close();
  file2.close();
  file3.close();
}