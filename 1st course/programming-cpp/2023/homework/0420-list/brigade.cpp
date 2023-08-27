#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>

using namespace std;

/* Використати контейнер list та його ітератор для роботи з масивами даних. Також реалізувати 
перехоплення винятків. 

В текстовому файлі знаходяться дані про витрати матеріалів бригад деякої будівельної фірми:
- номер бригади
- дані про бригадира
- список витрачених матеріалів:
  - з зазначенням дати
  - назви матеріалу
  - об’єму
  - вартості
Дані у файлі можуть повторюватися (для однієї бригади – декілька записів)

зчитати дані з файлу у контейнер і відобразити їх на екрані (і записати у відповідні файли) 
у зростаючому порядку номерів бригад. При цьому декілька даних про витрати для кожної бригади 
об’єднуються в одну.

Вивести загальний список використовуваних матеріалів (без повторів) із зазначенням загального 
їх об’єму і вартості. відобразити це у файлі */

struct Material
{
  string date;
  string name;
  double volume;
  double price;

  void Output(ostream &os)
  {
    os << name << ", " << date << ", " << volume << "m^3, $" << price << "; ";
  }

  void operator+=(const Material &m)
  {
    volume += m.volume;
    price += m.price;
  }
};

class Brigade
{
  int num_;
  vector<string> brigs_;
  
  public:
    vector<Material> mats_;

    void Input(istream &is)
    {
      string t;
      is >> t;
      brigs_.push_back(t);
      
      Material temp;
      is >> temp.date >> temp.name;
      is >> temp.volume >> temp.price;
      
      if(is.fail())
      {
        throw invalid_argument("Two last elements must be doubles");
      }

      mats_.push_back(temp);
    }

    void Output(ostream &os)
    {
      os << "brigade number: " << num_ << "\nbrigadiers: ";
      for(size_t i = 0; i < brigs_.size() - 1; i++)
      {
        os << brigs_[i] << ", ";
      }
      os << brigs_[brigs_.size() - 1] << "\n";
      
      os << "materials: ";
      for(size_t i = 0; i < mats_.size(); i++)
      {
        mats_[i].Output(os);
      }
      os << "\n\n";
    }

    void SetNum(int n)
    {
      num_ = n;
    }

    bool operator<(const Brigade &b)
    {
      return num_ < b.num_;
    }
};

template <typename T>

int IsElementIn(vector<T> arr, T el)
{
  for(int i = 0; i < arr.size(); i++)
  {
    if(arr[i] == el)
    {
      return i;
    }
  }
  return -1;
}

int main()
{
  try
  {
    list<Brigade*> arr;
    list<Brigade*>::iterator i;

    ifstream file1("input.txt");
    ofstream file2("output_brigades.txt");
    ofstream file3("output_materials.txt");

    vector<int> arr_num;

    while(!file1.eof())
    {
      int num;
      file1 >> num;
      
      if(file1.fail())
      {
        throw invalid_argument("Element must be integer");
      }

      int inx = IsElementIn(arr_num, num);
      if(inx != -1)
      {
        int inxx = 0;
        for(i = arr.begin(); i != arr.end(); i++)
        {
          if(inxx == inx)
          {
            (*i)->Input(file1);
          }
          inxx++;
        }
      }
      else
      {
        arr_num.push_back(num);
        Brigade* temp = new Brigade();
        temp->SetNum(num);
        temp->Input(file1);
        arr.push_back(temp);
      }
    }

    arr.sort([](Brigade* b1, Brigade* b2) { return (*b1) < (*b2); });

    for(i = arr.begin(); i != arr.end(); i++)
    {
      (*i)->Output(file2);
    }

    vector<Material> arr_mat;
    vector<string> arr_mat_names;

    for(i = arr.begin(); i != arr.end(); i++)
    {
      for(size_t j = 0; j < (*i)->mats_.size(); j++)
      {
        string name = (*i)->mats_[j].name;
        int inx = IsElementIn(arr_mat_names, name);
        if(inx != -1)
        {
          arr_mat[inx] += (*i)->mats_[j];
        }
        else
        {
          arr_mat_names.push_back(name);
          arr_mat.push_back((*i)->mats_[j]);
        }
      }
    }

    for(size_t i = 0; i < arr_mat.size(); i++)
    {
      arr_mat[i].Output(file3);
      file3 << "\n";
    }

    file1.close();
    file2.close();
    file3.close();
  }

  catch(invalid_argument &e)
  {
    cerr << e.what() << "\n";
  }
}