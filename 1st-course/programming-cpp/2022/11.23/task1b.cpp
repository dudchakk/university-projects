#include <iostream>
#include <cmath>

using namespace std;

enum Month
{
  JANUARY,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER
};

struct Date
{
  int day;
  Month month;
  int year;
};

Month StringToMonth(string name)
{
  int n = name.length();
  for(int i = 0; i < n; i++)
    if(name[i] >= 'A' && name[i] <= 'Z')
      name[i] = tolower(name[i]);
  
  if(name == "january" || name == "jan")
    return JANUARY;
  if(name == "february" || name == "feb")
    return FEBRUARY;
  if(name == "march" || name == "mar")
    return MARCH;
  if(name == "april" || name == "apr")
    return APRIL;
  if(name == "may")
    return MAY;
  if(name == "june" || name == "jn")
    return JUNE;
  if(name == "july" || name == "jl")
    return JULY;
  if(name == "august" || name == "aug")
    return AUGUST;
  if(name == "september" || name == "sep")
    return SEPTEMBER;
  if(name == "october" || name == "oct")
    return OCTOBER;
  if(name == "november" || name == "nov")
    return NOVEMBER;
  if(name == "december" || name == "dec")
    return DECEMBER;
}

bool dateIsGreater(Date d1, Date d2)
{
  if(d1.year > d2.year)
    return true;
  if(d1.month > d2.month)
    return true;
  if(d1.day > d2.day)
    return true;
  return false;
}

int main()
{
  Date arr[6];
  cout << "Enter 5 dates and today's date: " << endl;
  for(int i = 0; i < 6; i++)
  {
    string temp;
    cin >> arr[i].day >> temp >> arr[i].year;
    arr[i].month = StringToMonth(temp);
  }

  int iGreatestDate = 0;
  for(int i = 1; i < 5; i++)
    if(dateIsGreater(arr[i], arr[iGreatestDate]))
      iGreatestDate = i;

  cout << "The closest date is: " << arr[iGreatestDate].day << '.' << arr[iGreatestDate].month << '.' << arr[iGreatestDate].year << endl;
}