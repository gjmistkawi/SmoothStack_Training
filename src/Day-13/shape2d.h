#ifndef __shape2d_h__
#define __shape2d_h__

#include "vertex.h"

#define PI 3.14159

// Base

class Shape2D {
public:
    virtual float area(void) const = 0;
    //virtual float perimeter(void) const;
};


// Polys

class Polygon: public Shape2D {
public:
    virtual float perimeter() const = 0;
};

class Triangle: public Polygon {
private:
    Vertex* _vertices[3];

public:
    Triangle(Vertex v1, Vertex v2, Vertex v3);
    ~Triangle(void);

    float area(void) const;
    float perimeter(void) const;
};


// Quads

class Quadrilateral: public Polygon {
protected:
    Vertex* _vertices[4];
    Triangle* _split[2];

public:
    Quadrilateral(void);
    Quadrilateral(Vertex v1, Vertex v2, Vertex v3, Vertex v4);
    virtual ~Quadrilateral(void);

    virtual float area(void) const;
    virtual float perimeter(void) const;
};

class Trapezoid: public Quadrilateral {
public:
    Trapezoid(Vertex v1, Vertex v2, Vertex v3, Vertex v4);
    ~Trapezoid(void);
};

class Parallelogram: public Quadrilateral {
public:
    Parallelogram(void);
    Parallelogram(Vertex v1, Vertex v2, Vertex v3, Vertex v4);
    virtual ~Parallelogram(void);
};

class Rhombus: public Parallelogram {
public:
    Rhombus(Vertex v1, Vertex v2, Vertex v3, Vertex v4);
    virtual ~Rhombus(void);
};

class Rectangle: public Parallelogram {
protected:
    float _height, _width;

public:
    Rectangle(void);
    Rectangle(Vertex v1, Vertex v2, Vertex v3, Vertex v4);
    virtual ~Rectangle(void);

    //deep copy
    Rectangle(const Rectangle& r);
    Rectangle& operator=(const Rectangle& r);

    //move
    Rectangle(Rectangle&& r);
    Rectangle& operator=(Rectangle&& r);

    virtual float area(void) const;
    virtual float perimeter(void) const;
};

class Square: public Rectangle {
private:
    float _side;

public:
    Square(void);
    Square(Vertex v1, Vertex v2, Vertex v3, Vertex v4);
    ~Square(void);

    //deep copy
    Square(const Square& s);
    Square& operator=(const Square& s);

    //move
    Square(Square&& s);
    Square& operator=(Square&& s);

    float area(void) const;
    float perimeter(void) const;
};



// Ellipses

class Ellipse: public Shape2D {
private:
    float   _height;

protected:
    Vertex* _vertex;
    float   _width;

public:
    Ellipse(Vertex vertex, Vertex h_exterior, Vertex w_exterior);
    ~Ellipse(void);

    //deep copy
    Ellipse(const Ellipse& c);
    Ellipse& operator=(const Ellipse& c);

    //move
    Ellipse(Ellipse&& c);
    Ellipse& operator=(Ellipse&& c);

    virtual float area(void) const;
    //float perimeter(void) const;
    virtual float circumference() const;
};

class Circle: public Ellipse {
private:
    float _radius;

public:
    Circle(Vertex vertex, Vertex exterior);
    ~Circle(void);

    //deep copy
    Circle(const Circle& c);
    Circle& operator=(const Circle& c);

    //move
    Circle(Circle&& c);
    Circle& operator=(Circle&& c);

    float area(void) const;
    //float perimeter(void) const;
    float circumference(void) const;
    float diameter(void) const;
};

#endif