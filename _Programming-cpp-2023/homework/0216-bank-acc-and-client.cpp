#include <iostream>
using namespace std;

/* 1.Створіть клас для банківського рахунку та  клас Клієнт.

Клас Банківський рахунок повинен мати поля:
- Клієнт
- номера рахунку
- баланс
Повинен містити методи:
- додавання грошей на рахунок і знімання
- показ балансу 
- показ загальної інформації

Клас Клієнт повинен мати поля: 
- імʼя клієнта
- адреса 
- номер телефону

Ввести дані про 10 банківських рахунків, надати можливість пошуку рахунку за іменем клієнта та за адресою 
клієнта, надати меню для додавання чи зняття грошей з вибраного рахунку */

class Client
{
  string name_;
  string address_;
  string phone_num_;

  public:
    Client(): name_(""), address_(""), phone_num_("") {}
    Client(string n, string a, string p): name_(n), address_(a), phone_num_(n) {}
    
    string getName() { return name_; }
    string getAddress() { return address_; }

    friend ostream& operator<<(ostream &os, Client &c)
    {
      cout << "client name: " << c.name_ << ", address_: " << c.address_ << ", phone number: " << c.phone_num_; 
      return os;
    }
    
    friend istream& operator>>(istream &is, Client &c)
    {
      cout << "Enter client name, address and phone number: " << endl;
      cin >> c.name_ >> c.address_ >> c.phone_num_;
      return is;
    }
};

class BankAccount
{
  Client client;
  string accNum;
  float balance;

  public:
    BankAccount(): accNum(""), balance(0) {}

    void addMoney(float sum) { balance += sum; }
    void withdrawMoney(float sum) { balance -= sum; }
    Client getClient() {return client; }
    float getBalance() { return balance; }
    void showGeneralInformation();
    
    friend istream& operator>>(istream &is, BankAccount &b)
    {
      cout << "Enter bank account number and balance: " << endl;
      cin >> b.accNum >> b.balance;
      cin >> b.client;
      return is;
    }

    friend ostream& operator<<(ostream &os, BankAccount &b)
    {
      b.showGeneralInformation();
      return os;
    }
};

void BankAccount::showGeneralInformation()
{
  cout << "Bank account number: " << accNum << ", balance: " << balance << endl;
  cout << client << endl;
}

bool findByName(BankAccount* arr, int n, string nm)
{
  for(int i = 0; i < n; i++)
    if(arr[i].getClient().getName() == nm)
    {
      cout << arr[i];
      return true;
    }
  return false;
}

bool findByAddress(BankAccount* arr, int n, string ad)
{
  for(int i = 0; i < n; i++)
    if(arr[i].getClient().getAddress() == ad)
    {
      cout << arr[i];
      return true;
    }
  return false;
}

int main()
{
  BankAccount* arr = new BankAccount[5];
  for(int i = 0; i < 5; i++)
    cin >> arr[i];
  
  cout << "---" << endl;

  for(int i = 0; i < 5; i++)
    cout << arr[i];
  
  findByName(arr, 5, "Anna");
  findByAddress(arr, 5, "Zelena,12");

  arr[0].addMoney(234.9);
  arr[0].withdrawMoney(23.9);

  arr[0].showGeneralInformation();
}