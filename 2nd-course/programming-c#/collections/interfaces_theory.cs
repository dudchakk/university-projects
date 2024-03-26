class Point: ICloneable
{
    public object Clone()
    {
        return new Point(x, y);
    }
}

class Line_s: ICloneable
{
    public Line_s()
    {
        beg = new Point(); 
        end = new Point();
    }
    public Line_s(Point b, Point e)
    {
        beg = (Point)b.Clone();
        end = (Point)e.Clone();
    }
    public override string ToString()
    {
        return base.ToString() +" ["+beg+", "+end+ "]";
    }
    private Point beg;
    private Point end;
    
    public object Clone()
    {
        return new Line_s ((Point)beg.Clone(), (Point)end.Clone()) ;
    }
}

// ---------

public class Employee : IComparable
{
    public int CompareTo(object incomingobject) 
    {
        // Storing incoming object in temp variable of  
        // current class type 
        Employee incomingemployee = incomingobject as Employee;     
        return this.ID.CompareTo(incomingemployee.ID); 
    }  
}

int IComparable.CompareTo(object obj)
{
   Car c=(Car)obj;
   return String.Compare(this.make,c.make);
}