#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


struct Point 
{
  double x;
  double y;

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
};

double pointDistance(Point p1, Point p2)
{
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

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

    double findPerimeter() const
    {
      return pointDistance(p1, p2) + pointDistance(p2, p3) + pointDistance(p3, p4) + pointDistance(p1, p4);
    }

    bool ifRectangle()
    {
      if(pointDistance(p1, p2) == pointDistance(p3, p4) && pointDistance(p1, p4) == pointDistance(p2, p3))
        return true;
      return false;
    }
    bool ifSquare()
    {
      if(ifRectangle() && pointDistance(p1, p2) == pointDistance(p1, p4))
        return true;
      return false;
    }

    bool operator>(const Quadrangle& q2)
    {
      return findPerimeter() > q2.findPerimeter();
    }
};

void sort(Quadrangle* array, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = i + 1; j < n; j++)
		{
			if(array[i] > array[j])
			{
				Quadrangle temp = array[i];
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
	Quadrangle array[n];

	for (int i = 0; i < n; i++)
	{
		cout << "Enter quadrangle " << i + 1 << " information: " << endl;
		cin >> array[i];
	}

  cout << "--------" << endl;

  sort(array, n);

	cout << "Sorted quadrangle array: " << endl;
	for(int i = 0; i < n; i++)
  {
		cout << array[i] << endl;
    cout << "-" << endl;
  }
  
  cout << "--------" << endl;

	cout << "Quadrangles that are rectangles: " << endl;
	for(int i = 0; i < n; i++)
		if(array[i].ifRectangle())
    {
			cout << array[i] << endl;
      cout << "-" << endl;
    }

  cout << "--------" << endl;

	cout << "Quadrangles that are squares: " << endl;
	for(int i = 0; i < n; i++)
    if(array[i].ifSquare())
    {
		  cout << array[i] << endl;
      cout << "-" << endl;
    }
}