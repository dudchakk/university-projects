#include <iostream>
#include <vector>

using namespace std;

void PrintArray(vector<int>arr)
{
	for(int i = 0; i < arr.size(); i++)
	  cout << arr[i] << " ";
	cout << endl;
}

vector<int> LeonNums(int max_l) 
{
	vector<int> nums = { 1, 1 };
	while(nums.back() <= max_l)
		nums.push_back(nums[nums.size() - 2] + nums.back() + 1);
	return nums;
}

void GetChildTrees(int i, int k, vector<int> leo_nums, int& t_r, int& k_r, int& t_l, int& k_l)
{
	t_r = i - 1;
	k_r = k - 2;
	t_l = t_r - leo_nums[k_r];
	k_l = k - 1;
}

void RestoreHeap(vector<int>* arr, int i, vector<int> heap, vector<int> leo_nums)
{
	int last = heap.size() - 1;
	int k = heap.back();
	int j;

	while(last > 0)
	{
		j = i - leo_nums[k];

		if ((*arr)[j] > (*arr)[i] && (k < 2 || (*arr)[j] > (*arr)[i - 1] && (*arr)[j] > (*arr)[i - 2])) 
		{
			swap((*arr)[i], (*arr)[j]);
			cout << "Step: ";
			PrintArray(*arr);
			i = j;
			last--;
			k = heap[last];
		}
		else
			break;
	}

	int t_r, k_r, t_l, k_l;

	while (k >= 2)
	{
		GetChildTrees(i, k, leo_nums, t_r, k_r, t_l, k_l);
		if((*arr)[i] < (*arr)[t_r] || (*arr)[i] < (*arr)[t_l])
		{
			if ((*arr)[t_r] > (*arr)[t_l])
			{
				swap((*arr)[i], (*arr)[t_r]);
				cout << "Step: ";
				PrintArray(*arr);
				i = t_r;
				k = k_r;
			}
			else
			{
				swap((*arr)[i], (*arr)[t_l]);
				cout << "Step: ";
				PrintArray(*arr);
				i = t_l;
				k = k_l;
			}
		}
		else
			break;
	}
}

void SmoothSort(vector<int>* arr) 
{
	vector<int> leo_nums = LeonNums((*arr).size());
	vector<int> heap;

	for(int i = 0; i < (*arr).size(); i++)
	{
		if(heap.size() >= 2 && heap[heap.size() - 2] == heap[heap.size() - 1] + 1)
		{
			heap.pop_back();
			heap[heap.size() - 1] += 1;
		}
		else
		{
			if (heap.size() >= 1 && heap.back() == 1)
				heap.push_back(0);
			else 
				heap.push_back(1);
		}
		RestoreHeap(arr, i, heap, leo_nums);
	}

	int k;
	int t_r, k_r, t_l, k_l;

	for(int i = (*arr).size() - 1; i >= 0 ; i--)
	{
		if(heap.size() > 0 && heap.back() < 2)
			heap.pop_back();
		else
		if(heap.size() > 0)
		{
			k = heap.back();
			heap.pop_back();
			GetChildTrees(i, k, leo_nums, t_r, k_r, t_l, k_l);
			heap.push_back(k_l);
			RestoreHeap(arr, t_l, heap, leo_nums);
			heap.push_back(k_r);
			RestoreHeap(arr, t_r, heap, leo_nums);
		}
	}
}

int main()
{
	int n, temp;
	cout << "Enter array size: ";
	cin >> n;
	vector<int> arr;
	cout << "Enter array: ";
	for(int i = 0; i < n; i++)
	{
	  cin >> temp;
		arr.push_back(temp);
	}
	cout << endl;
	SmoothSort(&arr);
	cout << endl << "Sorted array: ";
	PrintArray(arr);
}