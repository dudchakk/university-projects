#include <iostream>
using namespace std;

class Student
{
  private:
    string name;
    int group;
    bool scholarship;
  
  public:
    Student(): name(""), group(1), scholarship(false) {}
    Student(string n, int g, bool s): name(n), group(g), scholarship(s) {}
    Student(const Student &s): name(s.name), group(s.group), scholarship(s.scholarship) {}

    friend istream &operator>>(istream &is, Student &s)
    {
      cout << "Enter student name: " << endl;
      is >> s.name;
      cout << "Enter student group: " << endl;
      is >> s.group;
      cout << "Enter 1, if student gets scholarship, and 0, if not: " << endl;
      is >> s.scholarship;
      return is;
    }
    
    friend ostream &operator<<(ostream &os, Student &s)
    {
      os << "student name: " << s.name << endl;
      os << "student group: " << s.group << endl;
      os << "student gets scholarship: " << s.scholarship << endl;
      
      return os;
    }
    
    string getName()
    {
      return name;
    }
    bool getScholarship()
    {
      return scholarship;
    }
    int getGroup() const
    {
      return group;
    }
    
    bool operator>(const Student& s2)
    {
      return getGroup() > s2.getGroup();
    }
    
    int incGroup()
    {
      group++;
      return group;
    }
};

void sort(Student* array, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = i + 1; j < n; j++)
		{
			if(array[i] > array[j])
			{
				Student temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}

int main()
{
  int n;
  cout << "Enter array count: " << endl;
  cin >> n;
	Student array[n];

	for (int i = 0; i < n; i++)
	{
		cout << "Enter student " << i + 1 << " information: " << endl;
		cin >> array[i];
	}

  cout << "--------" << endl;

	sort(array, n);

	cout << "Sorted students' group numbers: " << endl;
	for(int i = 0; i < n; i++)
		cout << array[i].getGroup() << endl;
  
  cout << "--------" << endl;

	cout << "Students who get scolarship: " << endl;
	for(int i = 0; i < n; i++)
		if(array[i].getScholarship())
			cout << array[i] << endl;

  cout << "--------" << endl;

	cout << "New students' group numbers: " << endl;
	for(int i = 0; i < n; i++)
	{
		array[i].incGroup();
		cout << array[i].getGroup() << endl;
	}
}