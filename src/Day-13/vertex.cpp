#include "vertex.h"

// Point

Vertex::Vertex(int x, int y): _x(x), _y(y) { }

Vertex::~Vertex(void) { }

Vertex::Vertex(const Vertex& v) {
    _x = v.x();
    _y = v.y();
}

Vertex& Vertex::operator=(const Vertex& v) {
    _x = v.x();
    _y = v.y();

    return *this;
}

int Vertex::x(void) const {
    return _x;
}

int Vertex::y(void) const {
    return _y;
}

// distance between 2 points
float Vertex::distance(const Vertex& p) const {
    return sqrt( pow((_x - p.x()), 2) 
               + pow((_y - p.y()), 2));
}