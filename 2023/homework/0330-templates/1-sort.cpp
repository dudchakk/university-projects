#include <iostream>
using namespace std;

/* Створити шаблонну функцію сортування і використати її для сортування:
- масиву цілих чисел
- рядків
- обʼєктів типу Person (структура з полями імʼя та адреса) за іменем. */

struct Person
{
  string name;
  string address;

  friend istream &operator>>(istream &is, Person &p)
  {
    is >> p.name >> p.address;
    return is;
  }

  friend ostream &operator<<(ostream &os, Person &p)
  {
    os << p.name << ", " << p.address;
    return os;
  }

  bool operator>(const Person &p)
  {
    return name > p.name;
  }
};

template <typename T>

void sort(T* array, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = i + 1; j < n; j++)
		{
			if(array[i] > array[j])
			{
				T temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}

int main()
{
  const int size = 5;

  cout << "Sorting array of 5 integers:" << endl;

  int* arr_int = new int[size];
  for(int i = 0; i < size; i++)
  {
    cin >> arr_int[i];
  }
  sort(arr_int, size);
  for(int i = 0; i < size; i++)
  {
    cout << arr_int[i] << " ";
  }

  cout << endl << endl << "Sorting array of 5 strings:" << endl;

  string* arr_str = new string[size];
  for(int i = 0; i < size; i++)
  {
    cin >> arr_str[i];
  }
  sort(arr_str, size);
  for(int i = 0; i < size; i++)
  {
    cout << arr_str[i] << " ";
  }

  cout << endl << endl<< "Sorting array of 5 persons:" << endl;

  Person* arr_per = new Person[size];
  for(int i = 0; i < size; i++)
  {
    cin >> arr_per[i];
  }
  sort(arr_per, size);
  for(int i = 0; i < size; i++)
  {
    cout << arr_per[i] << " " << endl;
  }
}