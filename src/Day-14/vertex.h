#ifndef __vertex_h__
#define __vertex_h__

#include "math.h"

class Vertex {
private:
    int _x;
    int _y;

public:
    Vertex(void);
    ~Vertex(void);
    Vertex(int x, int y);

    //deep copy
    Vertex(const Vertex& v);
    Vertex& operator=(const Vertex& v);

    int x(void) const;
    int y(void) const;

    float distance(const Vertex& p) const;
};

#endif