#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


class Point 
{
  private:
    double x;
    double y;

  public:
    Point(): x(0), y(0) {}
    Point(double xx, double yy): x(xx), y(yy) {}
    Point(const Point &p): x(p.x), y(p.y) {}

    friend istream &operator>>(istream &is, Point &p)
    {
      //cout << "Enter x, y: " << endl;
      is >> p.x >> p.y;
      return is;
    }

    friend ostream &operator<<(ostream &os, Point &p)
    {
      //cout << "x: " << p.x << ", y: " << p.y;
      return os;
    }

    double pointDistance(Point p)
    {
      return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    }
};
  

class Quadrangle 
{
  private:
    Point p1;
    Point p2;
    Point p3;
    Point p4;

  public:
    Quadrangle(): p1(), p2(), p3(), p4() {}
    Quadrangle(Point pp1, Point pp2, Point pp3, Point pp4): p1(pp1), p2(pp2), p3(pp3), p4(pp4) {}
    Quadrangle(const Quadrangle &q): p1(q.p1), p2(q.p2), p3(q.p3), p4(q.p4) {}

    friend istream &operator>>(istream &is, Quadrangle &q)
    {
      cout << "Enter point 1: " << endl;
      is >> q.p1;
      cout << "Enter point 2: " << endl;
      is >> q.p2;
      cout << "Enter point 3: " << endl;
      is >> q.p3;
      cout << "Enter point 4: " << endl;
      is >> q.p4;
      return is;
    }

    friend ostream &operator<<(ostream &os, Quadrangle &q)
    {
      os << "point 1: " << q.p1 << endl;
      os << "point 2: " << q.p2 << endl;
      os << "point 3: " << q.p3 << endl;
      os << "point 4: " << q.p4 << endl;
      
      return os;
    }

    double findPerimeter(Quadrangle q)
    {
      return q.p1.pointDistance(q.p2) + q.p2.pointDistance(q.p3) + q.p3.pointDistance(q.p4) + q.p1.pointDistance(q.p4);
    }
};


int main()
{
  Quadrangle q1;
  //cout << "Enter quadrangle's points: " << endl;
  cin >> q1;
  //cout << q1 << endl;
  //cout << q1.findPerimeter(q1) << endl;

  /*Point p1, p2;
  cin >> p1 >> p2;
  cout << p1.pointDistance(p2);*/

}