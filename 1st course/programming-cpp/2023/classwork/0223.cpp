#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student
{
  string name;
  
  public:
    Student(): name("") {}

    friend istream &operator>>(istream &is, Student &s)
    {
      cout << "Enter student name: " << endl;
      cin >> s.name;
      return is;
    }
    
    friend ostream &operator<<(ostream &os, Student &s)
    {
      os << "student name: " << s.name << endl;
      return os;
    }

    string getName() { return name; }
    void setName(string n) { name = n; }
};

class Group
{
  Student* st_arr;
  int st_cnt;
  string grp_name;
  int year;

  public:
    Group(): st_cnt(0), grp_name(""), year(0) { st_arr = new Student[st_cnt]; }
    Group(Student* sa, int sc, string gn, int y): st_cnt(sc), grp_name(gn), year(y) 
    {
      st_arr = new Student[st_cnt];
		  for (int i = 0;i < st_cnt; i++)
		    st_arr[i] = sa[i];
    }
    Group(const Group &g): st_cnt(g.st_cnt), grp_name(g.grp_name), year(g.year) 
    {
      st_cnt = g.st_cnt;
      st_arr = new Student[st_cnt];
      for (int i = 0; i<st_cnt; i++)
        st_arr[i] = g.st_arr[i];
    }
    ~Group() { if(st_arr != 0) delete[] st_arr; }

    Group& operator=(const Group &g)
    {
      if(this != &g)
      {
        if(st_arr != 0)
          delete[] st_arr;
        st_arr = new Student[st_cnt = g.st_cnt];
        for(int i = 0; i < st_cnt; i++)
          st_arr[i] = g.st_arr[i];
        st_cnt = g.st_cnt;
        grp_name = g.grp_name;
        year = g.year;
      }
      return *this;
    }

    Student& operator[](size_t pos)
    {
      if(pos < st_cnt)
        return st_arr[pos];
      cout << "error: out of range";
    }

    friend istream &operator>>(istream &is, Group &g)
    {
      cout << "Enter student count: " << endl;
      is >> g.st_cnt;
      for(int i = 0; i < g.st_cnt; i++)
        cin >> g.st_arr[i];
      cout << "Enter group name and year of admission: " << endl;
      is >> g.grp_name >> g.year;
      return is;
    }
    
    friend ostream &operator<<(ostream &os, Group &g)
    {
      os << "Student count: " << g.st_cnt << ", group name: " << g.grp_name << ", year of admission: " << g.year << endl;
      cout << "students: " << endl;
      for(int i = 0; i < g.st_cnt; i++)
        cout << g.st_arr[i];
      return os;
    }

    int getStudentCount() { return st_cnt; }
    void setStudentCount(int s) { st_cnt = s; }
    string getName() { return grp_name; }
    void setName(string n) { grp_name = n; }
    int getYearOfAdmission() { return year; }
    void setYearOfAdmission(int y) { year = y; }
    void setStudents(Student* sa, int s)
    {
      for(int i = 0; i < s; i++)
        sa[i] = st_arr[i];
    }
    Student* getStudents(int &sc) { return st_arr; }
};

int main()
{
  Group g1, g2;
  cin >> g1;
  cin >> g2;
}