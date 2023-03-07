#include <iostream>
using namespace std;

int * sort(int *array, int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (array[j] > array[j + 1])
      {
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
  return array;
}

int main()
{
  int n;
  cout << "Enter array count: " << endl;
  cin >> n;

  int *array = new int[n];
  cout << "Enter array elements: " << endl;
  for (int i = 0; i < n; i++)
    cin >> array[i];

  int *sArray = sort(array, n);

  cout << "Sorted array: " << endl;
  for (int i = 0; i < n; i++)
  {
    cout << sArray[i] << endl;
  }
}