#include <cassert>
#include <iostream>
#include <string>
#include "shape2d.h"

using namespace std;

int main(void) {
    Vertex s1(0,0);
    Vertex s2(0,3);
    Vertex s3(3,3);
    Vertex s4(3,0);

    Vertex q1(1,0);
    Vertex q2(4,5);
    Vertex q3(3,6);
    Vertex q4(0,1);

    Vertex t1(0,0);
    Vertex t2(7,0);
    Vertex t3(5,3);
    Vertex t4(2,3);

    Vertex r1(0,0);
    Vertex r2(8,0);
    Vertex r3(8,4);
    Vertex r4(0,4);

    Vertex e1(0,0);
    Vertex e2(0,4);
    Vertex e3(0,8);

    Ellipse e(e1, e2, e3);
    cout << "Ellipse area: " << e.area() << endl;
    cout << endl;

    Circle c(e1, e2);
    cout << "Circle area: " << c.area() << endl;
    cout << "Circle circumference: " << c.circumference() << endl;
    cout << endl;


    Triangle tri(s1, s2, s3);
    cout << "Triangle area: " << tri.area() << endl;
    cout << "Triangle perimeter: " << tri.perimeter() << endl;
    cout << endl;

    Quadrilateral q(q1, q2, q3, q4);
    cout << "Quadrilateral area: " << q.area() << endl;
    cout << "Quadrilateral perimeter: " << q.perimeter() << endl;
    cout << endl;

    Trapezoid trap(t1, t2, t3, t4);
    cout << "Trapezoid area: " << trap.area() << endl;
    cout << "Trapezoid perimeter: " << trap.perimeter() << endl;
    cout << endl;

    Rectangle rec(r1, r2, r3, r4);
    cout << "Rectangle area: " << rec.area() << endl;
    cout << "Rectangle perimeter: " << rec.perimeter() << endl;
    cout << endl;

    Square sqr(s1, s2, s3, s4);
    cout << "Square area: " << sqr.area() << endl;
    cout << "Square perimeter: " << sqr.perimeter() << endl;
    cout << endl;

    Shape2D* shape = new Square(s1, s2, s3, s4);
    cout << "Shape2D area: " << shape->area() << endl;
    cout << endl;

    Polygon* pol = new Rectangle(r1, r2, r3, r4);
    cout << "Polygon area: " << pol->area() << endl;
    cout << "Polygon perimeter: " << pol->perimeter() << endl;
    cout << endl;

    return 0;
}