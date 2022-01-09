#include "shape2d.h"


#include<iostream>
using namespace std;

// Triangle
Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3) {
    _vertices[0] = new Vertex(v1);
    _vertices[1] = new Vertex(v2);
    _vertices[2] = new Vertex(v3);
}

Triangle::~Triangle(void) {
    for(int i = 0; i < 3; i++)
        delete _vertices[i];
}

float Triangle::area(void) const {
    float p = perimeter() / 2.0;
    float a = _vertices[0]->distance(*_vertices[1]);
    float b = _vertices[1]->distance(*_vertices[2]);
    float c = _vertices[2]->distance(*_vertices[0]);
    float area = sqrt(p * (p - a) * (p - b) * (p - c));

    return area;
}

float Triangle::perimeter(void) const {
    float length = 0;
    length += _vertices[0]->distance(*_vertices[1]);
    length += _vertices[1]->distance(*_vertices[2]);
    length += _vertices[2]->distance(*_vertices[0]);

    return length;
}


// Quadrilateral

Quadrilateral::Quadrilateral(void) {
    for(int i = 0; i < 4; i++)
        _vertices[i] = nullptr;
}

Quadrilateral::Quadrilateral(Vertex v1, Vertex v2, Vertex v3, Vertex v4) {
    _vertices[0] = new Vertex(v1);
    _vertices[1] = new Vertex(v2);
    _vertices[2] = new Vertex(v3);
    _vertices[3] = new Vertex(v4);

    _split[0] = new Triangle(*_vertices[0], *_vertices[1], *_vertices[2]);
    _split[1] = new Triangle(*_vertices[3], *_vertices[1], *_vertices[2]);
}

Quadrilateral::~Quadrilateral(void) {
    for(int i = 0; i < 4; i++)
        delete _vertices[i];

    for(int i = 0; i < 2; i++)
        delete _split[i];
}

float Quadrilateral::area(void) const {
    cout << "quad call - ";
    return _split[0]->area() + _split[1]->area();
}

float Quadrilateral::perimeter(void) const {
    float length = 0;
    length += _vertices[0]->distance(*_vertices[1]);
    length += _vertices[1]->distance(*_vertices[2]);
    length += _vertices[2]->distance(*_vertices[3]);
    length += _vertices[3]->distance(*_vertices[0]);

    cout << "quad call - ";
    return length;
}


// Trapezoid

Trapezoid::Trapezoid(Vertex v1, Vertex v2, Vertex v3, Vertex v4): 
    Quadrilateral(v1, v2, v3, v4) { }

Trapezoid::~Trapezoid(void) { }


// Parallelogram 

Parallelogram::Parallelogram(void) { }

Parallelogram::Parallelogram(Vertex v1, Vertex v2, Vertex v3, Vertex v4):
    Quadrilateral(v1, v2, v3, v4) { }

Parallelogram::~Parallelogram(void) { }


// Parallelogram 

Rhombus::Rhombus(Vertex v1, Vertex v2, Vertex v3, Vertex v4):
    Parallelogram(v1, v2, v3, v4) { }

Rhombus::~Rhombus(void) { }


// Rectangle

Rectangle::Rectangle() { }

Rectangle::Rectangle(Vertex v1, Vertex v2, Vertex v3, Vertex v4):
    Parallelogram(v1, v2, v3, v4) {
    _height = _vertices[0]->distance(*_vertices[1]);
    _width  = _vertices[1]->distance(*_vertices[2]);
}

Rectangle::~Rectangle(void) { }

Rectangle::Rectangle(const Rectangle& r) {
    for(int i = 0; i < 4; i++)
        _vertices[i] = new Vertex(*r._vertices[i]);

    _height = _vertices[0]->distance(*_vertices[1]);
    _width  = _vertices[1]->distance(*_vertices[2]);
}

Rectangle& Rectangle::operator=(const Rectangle& r) {
    for(int i = 0; i < 4; i++)
        _vertices[i] = new Vertex(*r._vertices[i]);

    _height = _vertices[0]->distance(*_vertices[1]);
    _width  = _vertices[1]->distance(*_vertices[2]);

    return *this;
}

Rectangle::Rectangle(Rectangle&& r) {
    for(int i = 0; i < 4; i++) {
        _vertices[i] = new Vertex(*r._vertices[i]);
        r._vertices[i] = nullptr;
    }

    _height = r._height;
    _width = r._width;

    //r._height = 0;
    //r._width = 0;
}

Rectangle& Rectangle::operator=(Rectangle&& r) {
    if(this == &r) return *this;

    for(int i = 0; i < 4; i++) {
        if(_vertices[i] != nullptr)
            delete _vertices[i];

        _vertices[i] = r._vertices[i];
        r._vertices[i] = nullptr;
    }

    _height = r._height;
    _width = r._width;

    return *this;
}

float Rectangle::area(void) const {
    cout << "rec call - ";
    return _width * _height;
}

float Rectangle::perimeter(void) const {
    cout << "rec call - ";
    return (2 * _width) + (2 * _height);
}


// Square

Square::Square() { }

Square::Square(Vertex v1, Vertex v2, Vertex v3, Vertex v4):
    Rectangle(v1, v2, v3, v4) {
    _side = _vertices[0]->distance(*_vertices[1]);
}

Square::~Square(void) { }

Square::Square(const Square& r) {
    for(int i = 0; i < 4; i++)
        _vertices[i] = new Vertex(*r._vertices[i]);

    _side = _vertices[0]->distance(*_vertices[1]);
}

Square& Square::operator=(const Square& r) {
    for(int i = 0; i < 4; i++)
        _vertices[i] = new Vertex(*r._vertices[i]);

    _side = _vertices[0]->distance(*_vertices[1]);

    return *this;
}

Square::Square(Square&& r) {
    for(int i = 0; i < 4; i++) {
        _vertices[i] = r._vertices[i];
        r._vertices[i] = nullptr;
    }

    _side = r._side;
}

Square& Square::operator=(Square&& r) {
    if(this == &r) return *this;

    for(int i = 0; i < 4; i++) {
        if(_vertices[i] != nullptr)
            delete _vertices[i];

        _vertices[i] = r._vertices[i];
        r._vertices[i] = nullptr;
    }

    _side = r._side;

    return *this;
}

float Square::area(void) const {
    cout << "sqr call - ";
    return _side * _side;
}

float Square::perimeter(void) const {
    cout << "sqr call - ";
    return 4 * _side;
}


// Ellipse

Ellipse::Ellipse(Vertex vertex, Vertex h_exterior, Vertex w_exterior) {
    _vertex = new Vertex(vertex);

    _height = _vertex->distance(h_exterior);
    _width  = _vertex->distance(w_exterior);
}

Ellipse::~Ellipse(void) {
    delete _vertex;
}

float Ellipse::area(void) const {
    return PI * _height * _width;
}


// Circle

Circle::Circle(Vertex vertex, Vertex exterior):
    Ellipse(vertex, exterior, exterior) {
    _radius = _width;
}

Circle::~Circle(void) { }

float Circle::area(void) const {
    return PI * _radius * _radius;
}

float Circle::circumference(void) const {
    return 2 * PI * _radius;
}

float Circle::diameter(void) const {
    return 2 * _radius;
}