#include <iostream>
using namespace std;

void arrSort(int* arr, int n)
{
  for(int i = 0; i < n; i++)
    for(int j = i + 1; j < n; j++)
      if(arr[i] > arr[j])
      {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
}

int main()
{
  int n;
  cout << "Enter n: " << endl;
  cin >> n;
  int arr[n];
  cout << "Enter array elements: " << endl;
  for(int i = 0; i < n; i++)
    cin >> arr[i];

  cout << "--------" << endl;
  
  for(int i = 0; i < n; i++)
    cout << arr[i] << ' ';
  cout << endl;
  arrSort(arr, n);
  for(int i = 0; i < n; i++)
    cout << arr[i] << ' ';
}