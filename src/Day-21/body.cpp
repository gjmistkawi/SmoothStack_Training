#include <vector>
#include <math.h>

class R {
public:
    double x;
    double y;

    R() {}
    R(double x, double y): x(x), y(y) {}
};

class V {
public:
    double v_x;
    double v_y;

    V() {}
    V(double x, double y): v_x(x), v_y(y) {}

    V operator+=(const V& v) {
        v_x += v.v_x;
        v_y += v.v_y;
        return *this;
    }
};

class F {
public:
    double f_x;
    double f_y;

    F() {}
    F(double x, double y): f_x(x), f_y(y) { }

    F operator+=(const F& f) {
        f_x += f.f_x;
        f_y += f.f_y;
        return *this;
    }
};

class A{
public:
    double a_x;
    double a_y;

    A() {}
    A(double x, double y): a_x(x), a_y(y) {}

    A operator+=(const A& a) {
        a_x += a.a_x;
        a_y += a.a_y;
        return *this;
    }
};

class Body {
public:
    int index; // index of body
    double mass;
    R position;
    V velocity;
    std::vector<F> forceVector;
    F totalForce;
    A acceleration;

    Body();
    Body(int i, double x, double y, double m): index(i), mass(m), 
        totalForce(F(0,0)), acceleration(A(0,0)), velocity(V(0,0)) {
        position = R(x,y);
        forceVector = std::vector<F>();
    }
};