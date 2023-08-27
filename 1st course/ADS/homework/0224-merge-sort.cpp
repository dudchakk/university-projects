#include <iostream>
using namespace std;

void PrintArray(int* arr, size_t n)
{
	for(int i = 0; i < n; i++)
	  cout << arr[i] << " ";
	cout << endl;
}

void MergeArrays(int* arr_one, size_t size_one, int* arr_two, size_t size_two, int* arr_three, size_t size)
{
  int i1 = 0, i2 = 0, i3 = 0;
  for(; i1 < size_one && i2 < size_two; i3++)
  {
    if(arr_one[i1] > arr_two[i2])
    {
      arr_three[i3] = arr_two[i2];
      cout << "Step: ";
      PrintArray(arr_three, size);
      i2++;
    }
    else
    {
      arr_three[i3] = arr_one[i1];
      cout << "Step: ";
      PrintArray(arr_three, size);
      i1++;
    }
  }

  for(; i1 < size_one; i1++, i3++)
  {
    arr_three[i3] = arr_one[i1];
    cout << "Step: ";
    PrintArray(arr_three, size);
  }
  for(; i2 < size_two; i2++, i3++)
  {
    arr_three[i3] = arr_two[i2];  
    cout << "Step: ";
    PrintArray(arr_three, size);
  }

  delete[] arr_one;
  delete[] arr_two;
}

bool MergeSort(int* arr, size_t size)
{
  if(size == 0)
    return false;
  if(size == 1)
    return true;

  size_t len1 = size / 2;
  int* arr_one = new int[len1];
  for(int i = 0; i < len1; i++)
    arr_one[i] = arr[i];

  size_t len2 = size - len1;
  int* arr_two = new int[len2];
  for(int i = 0; i < len2; i++)
    arr_two[i] = arr[i + len1];
  
  MergeSort(arr_one, len1);
  MergeSort(arr_two, len2);
  MergeArrays(arr_one, len1, arr_two, len2, arr, size);
  return true;
}

int main()
{
  size_t n;
  cout << "Enter array size: ";
	cin >> n;
  int* arr = new int[n];
  cout << "Enter array: ";
  for(int i = 0; i < n; i++)
    cin >> arr[i];
  
  cout << endl;
  MergeSort(arr, n);
  cout << endl << "Sorted array: ";
	PrintArray(arr, n);
}