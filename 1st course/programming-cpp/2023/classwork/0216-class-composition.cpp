#include <iostream>
#include <vector>
using namespace std;

/* Розробити програму для кошика електронного магазину, яка дозволить користувачам додавати товари в кошик 
для подальшої покупки. Програма має забезпечувати додавання товарів до кошика, видалення товарів з кошика, 
відображення списку товарів у кошику, а також обчислення сумарної вартості кошика. Товар має назву, ціну 
за одиницю. У кошик можна додавати товар і вказувати його кількість, так само з видаленням. */

class Product
{
  string name_;
  float price;
  int code;
  bool state;

  public:
    Product(): name_(""), price(0), code(0), state(true) {}
    string getName() { return name_; }
    int getCode() { return code; }
    float getPrice() { return price; }
    bool getState() { return state; }
    void setState(bool b) { state = b; }

    friend ostream& operator<<(ostream& os, Product& p)
    {
      cout << "product name_: " << p.name_ << ", price: " << p.price;
    }
};

class Basket
{
  Product* products;
  int* counts;
  int cur;

  public:
    Basket(): cur(0) { products = new Product[100]; counts = new int[100]; }
    void addProduct(Product p, int count) { products[cur] = p; counts[cur] = count; }
    void removeProduct(Product p);
    void productList();
};

void Basket::removeProduct(Product p)
{
  for(int i = 0; i < products.size(); i++)
    if(products[i].getCode() == p.getCode())
      products[i].setState(false);
}

void Basket::productList()
{
  for(int i = 0; i < products.size(); i++)
  {
    cout
  }
}

int main()
{
  
}