#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

/* 5. В текстовому файлі задані дані про розміщення букв у тексті: набір буква-список позицій, на яких вона 
стоїть у тексті.
- Визначити необхідні типи  
- ввести дані з файлу 
- вивести в файл1 повний текст, що відповідає введеним даним. 
- вивести у файл2, букви, посортовані за їх кількістю у тексті. */

/*
ababgghb - 8
a 0 2
b 1 3 7
g 4 5
h 6
*/

void print_map(const map<char, vector<int>>& m)
{
  for(const auto& [key, value] : m)
  {
    cout << '[' << key << "] = ";
    for(size_t i = 0; i < value.size(); i++)
    {
      cout << value[i] << " ";
    }
    cout << "\n";
  }
}

string print_text(const map<char, vector<int>>& m)
{
  size_t letter_cnt = 0;
  for(const auto& [key, value] : m)
  {
    letter_cnt += value.size();
  }
  
  string res;
  res.resize(letter_cnt);
  for(const auto& [key, value] : m)
  {
    for(size_t i = 0; i < value.size(); i++)
    {
      res[value[i]] = key;
    }
  }
  return res;
}

bool cmp(pair<char, vector<int>>& a, pair<char, vector<int>>& b)
{
  return a.second.size() > b.second.size();
}

vector<pair<char, vector<int>>> sort_map(map<char, vector<int>>& m)
{
  vector<pair<char, vector<int>>> arr;
 
  for(auto& it : m)
  {
    arr.push_back(it);
  }
  sort(arr.begin(), arr.end(), cmp);
  
  return arr;
}

int main()
{
  ifstream file1("input.txt");
  ofstream file2("output_text.txt");
  ofstream file3("output_sorted.txt");

  map<char, vector<int>> arr;
  
  string str;
  while(getline(file1, str))
  {
    istringstream ss(str);
    char letter;
    ss >> letter;
    
    vector<int> poss;
    int num;
    while(ss >> num)
    {
      poss.push_back(num);
    }

    arr[letter] = poss;
  }

  //print_map(arr);
  file2 << print_text(arr);

  vector<pair<char, vector<int>>> res = sort_map(arr);
  
  for(size_t i = 0; i < res.size(); i++)
  {
    file3 << res[i].first << ": ";
    for(size_t j = 0; j < res[i].second.size(); j++)
    {
      file3 << res[i].second[j] << " ";
    }
    file3 << "\n";
  }

  file1.close();
  file2.close();
  file3.close();
}