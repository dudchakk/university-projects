#include <iostream>
using namespace std;

/* Створити клас Університет, та класи Студент та Курс. 

Клас університету повинен мати поля:
- назва університету 
- місце розташування
- масив студентів
- масив курсів
Клас Студент повинен мати поля:
- імені студента
- ідентифікаційного номера
- спеціальності
Клас Курс повинен мати поля:
- назви курсу
- номера курсу
- спеціальність, для якої цей курс проводиться

В класі Університет додати методи:
- додавання-видалення студентів та курсів
- формування за вказаним курсом списку студентів, які мали б цей курс прослухати
- формування списку курсів, які би мав цей студент прослухати
- виведення всіх студентів 
- виведення всіх курсів

Ввести дані про університет, надати меню для додавання-видалення курсів та студентів, а також формування 
списку студентів за вказаним курсом та список курсів для вказаного студента */

const int MAX_SIZE = 100;

class Student
{
  string name_;
  int id_;
  string* specialties_;
  int sp_cnt_;

  public:
    Student(): name_(""), id_(-1), sp_cnt_(0)
    {
      specialties_ = new string[MAX_SIZE];
    }
    Student(string n, int id): name_(n), id_(id), sp_cnt_(0)
    {
      specialties_ = new string[MAX_SIZE];
    }
    ~Student()
    {
      if(specialties_ != 0)
        delete[] specialties_;
    }
    
    string getName() { return name_; }
    int getId() { return id_; }
    string* getSpecialties() { return specialties_; }

    bool isSpecialty(string spec)
    {
      for(int i = 0; i < sp_cnt_; i++)
        if(specialties_[i] == spec)
          return true;
      return false;
    }

    bool addSpecialty(string s)
    {
      if(sp_cnt_ >= MAX_SIZE)
        return false;
      
      specialties_[sp_cnt_] = s;
      sp_cnt_++;
      return true;
    }

    friend ostream &operator<<(ostream & os, Student &s)
    {
      cout << s.name_ << "; " << s.id_ << "; specialties: ";
      if(s.sp_cnt_ == 0)
      {
        cout << "no";
        return os;
      }
      for(int i = 0; i < s.sp_cnt_ - 1; i++)
        cout << s.specialties_[i] << ", ";
      cout << s.specialties_[s.sp_cnt_ - 1];

      return os;
    }
};

class Course
{
  string name_;
  int id_;
  string spec_;

  public:
    Course(): name_(""), id_(-1), spec_("") {}
    Course(string n, int id, string s): name_(n), id_(id), spec_(s) {}

    string getName() { return name_; }
    int getId() { return id_; }
    string getSpecialty() { return spec_; }

    friend ostream& operator<<(ostream &os, Course &c)
    {
      cout << c.name_ << ", " << c.id_ << ", " << c.spec_;
      return os;
    }
};

class University
{
  string name_;
  string loc_;
  Student* students_;
  int st_cnt_;
  Course* courses_;
  int crs_cnt_;

  public:
    University(string n, string l): name_(n), loc_(l), st_cnt_(0), crs_cnt_(0)
    {
      students_ = new Student[MAX_SIZE];
      courses_ = new Course[MAX_SIZE];
    }
    ~University()
    {
      if(students_ != 0)
        delete[] students_;
      if(courses_ != 0)
        delete[] courses_;
    }

    bool addStudent(Student s)
    {
      if(st_cnt_ >= MAX_SIZE)
        return false;
      
      students_[st_cnt_] = s;
      st_cnt_++;
      return true;
    }

    bool removeStudent(int id)
    {
      for(int i = 0; i < st_cnt_; i++) 
        if(students_[i].getId() == id) 
        {
          for(int j = i; j < st_cnt_; j++)
            students_[j] = students_[j + 1];
          st_cnt_--;
          return true;
        }

      return false;
    } 

    bool addCourse(Course c)
    {
      if(crs_cnt_ >= MAX_SIZE)
        return false;
      
      courses_[crs_cnt_] = c;
      crs_cnt_++;
      return true;
    }

    bool removeCourse(int id)
    {
      for(int i = 0; i < crs_cnt_; i++) 
        if(courses_[i].getId() == id) 
        {
          for(int j = i; j < crs_cnt_; j++)
            courses_[j] = courses_[j + 1];
          crs_cnt_--;
          return true;
        }

      return false;
    } 

    bool printStudentsByCourse(int id)
    {
      string spec;
      for(int i = 0; i < crs_cnt_; i++)
      {
        if(courses_[i].getId() == id)
        {
          spec = courses_[i].getSpecialty();
          break;
        }
        return false;
      }

      for(int i = 0; i < st_cnt_; i++)
        if(students_[i].isSpecialty(spec))
          cout << '-' << endl << students_[i] << endl;
      return true;
    }

    void printAllStudents()
    {
      cout << "Students:" << endl;
      if(st_cnt_ == 0)
        cout << "No students" << endl;

      for(int i = 0; i < st_cnt_; i++)
        cout << students_[i] << endl;
    }

    void printAllCourses()
    {
      cout << "Courses: " << endl;
      if(crs_cnt_ == 0)
        cout << "No courses" << endl;
      
      for(int i = 0; i < crs_cnt_; i++)
        cout << courses_[i] << endl;
    }
};

int main()
{
  University uni("LNU", "Universytetska, 1");
  
  Student s1("Ivan", 1);
  Student s2("Maria", 3);
  Student s3("Sasha", 2);

  s1.addSpecialty("bio");
  s1.addSpecialty("math");
  s2.addSpecialty("geo");
  
  uni.addStudent(s1);
  uni.addStudent(s2);
  uni.addStudent(s3);

  uni.printAllStudents();

  cout << "-----" << endl;
  
  Course c1("math", 1, "math");
  Course c2("bio", 2, "bio");
  Course c3("geo", 4, "geo");

  uni.addCourse(c1);
  uni.addCourse(c2);
  uni.addCourse(c3);

  uni.printAllCourses();
}