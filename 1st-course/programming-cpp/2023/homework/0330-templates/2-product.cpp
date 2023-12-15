#include <iostream>
using namespace std;

/* Визначити шаблонний клас Товар:
- деякий об’єкт Т
- дату його виготовлення
- термін придатності (в днях). 
В класі визначити: 
- оператори<< і >>
- метод, який повертає дату кінцевого терміну придатності

Також визначити структуру Молоко:
- назва
- жирність
+ оператори << і >>

Створити два масиви Товарів з шаблонними параметрами string та Молоко. Ввести дані про декілька 
таких об’єктів і видрукувати для кожного кінцевий термін придатності. */

struct Milk
{
  string name;
  double greasiness;

  friend istream &operator>>(istream &is, Milk &m)
  {
    cout << "Enter milk name and greasiness: ";
    is >> m.name >> m.greasiness;
    return is;
  }

  friend ostream &operator<<(ostream &os, Milk &m)
  {
    os << m.name << ", " << m.greasiness;
    return os;
  }
};

template <typename T>

class Product
{
  T obj_;
  string man_date_;
  int exp_date_;

  public:
    Product(): obj_(), man_date_(""), exp_date_(0) {}
    
    friend istream &operator>>(istream &is, Product &p)
    {
      is >> p.obj_;
      cout << "Enter product date of manufacture and expiration date: ";
      is >> p.man_date_ >> p.exp_date_;
      return is;
    }

    friend ostream &operator<<(ostream &os, Product &p)
    {
      os << p.obj_ << ", date of manufacture: " << p.man_date_ << ", expiration date: " << p.exp_date_;
      return os;
    }

    int GetExpirationDate()
    {
      return exp_date_;
    }
};

int main()
{
  const int size = 3;

  cout << "Product string:" << endl;

  Product<string>* arr_str = new Product<string>[size];
  for(int i = 0; i < size; i++)
  {
    cout << "Enter a string: ";
    cin >> arr_str[i];
  }
  cout << "Expiration dates:" << endl;
  for(int i = 0; i < size; i++)
  {
    cout << arr_str[i].GetExpirationDate() << endl;
  }

  cout << endl << "Product Milk:" << endl;

  Product<Milk>* arr_milk = new Product<Milk>[size];
  for(int i = 0; i < size; i++)
  {
    cin >> arr_milk[i];
  }
  cout << "Expiration dates:" << endl;
  for(int i = 0; i < size; i++)
  {
    cout << arr_milk[i].GetExpirationDate() << endl;
  }
}