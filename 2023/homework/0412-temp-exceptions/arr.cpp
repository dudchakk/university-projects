#include <iostream>
using namespace std;

template <typename T>

T* ModifyArray(T* arr, int &n)
{
  int new_n = (n % 2 == 0) ? (n + n / 2) : (n + n / 2 + 1);
  T* new_arr = new T[new_n];

  size_t i1 = 0, i2 = 0;
  for(; i1 < n; i1++, i2++)
  {
    new_arr[i2] = arr[i1];
    if(i1 % 2 == 0)
    {
      new_arr[++i2] = arr[i1];
    }
  }

  n = new_n;
  return new_arr;
}

int main()
{
  try
  {  
    cout << "Modify array of integers:" << endl << endl;

    cout << "Enter array size: ";
    int n1;
    cin >> n1;
    
    if(n1 <= 0)
    {
      throw out_of_range("Invalid size: must be positive");
    }

    int* arr_int = new int[n1];

    cout << "Enter array elements: ";
    for(size_t i = 0; i < n1; i++)
    {
      cin >> arr_int[i];
    }

    if(cin.fail())
    {
      throw invalid_argument("Elements must be integers");
    }
    
    int* new_arr_int = ModifyArray(arr_int, n1);

    cout << "Modified: ";
    for(size_t i = 0; i < n1; i++)
    {
      cout << new_arr_int[i] << " ";
    }

    cout << endl << endl << "Modify array of strings:" << endl;
    
    cout << "Enter array size: ";
    int n2;
    cin >> n2;
    
    if(n2 <= 0)
    {
      throw out_of_range("Invalid size: must be positive");
    }

    string* arr_str = new string[n2];

    cout << "Enter array elements: ";
    for(size_t i = 0; i < n2; i++)
    {
      cin >> arr_str[i];
    }

    if(cin.fail())
    {
      throw invalid_argument("Elements must be strings");
    }

    string* new_arr_str = ModifyArray(arr_str, n2);

    cout << "Modified: ";
    for(size_t i = 0; i < n2; i++)
    {
      cout << new_arr_str[i] << " ";
    }
  }

  catch(const invalid_argument &e)
  {
    cerr << e.what() << endl;
  }

  catch(const out_of_range &e)
  {
    cerr << e.what() << endl;
  }
}