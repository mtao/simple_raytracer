#ifndef RAY_HPP
#define RAY_HPP
#include "types.hpp"

struct Ray {
    Ray(const Point& o = Point::Zero(), const Vector& d = Vector::Zero()): o(o), d(d) {}
    Ray apply(const AffineTransform& T) const {
        return Ray( T * o, T.linear() * d );
    }
    Point eval(double t) const {
        return o + t*d;
    }

    Point o;
    Vector d;

};

#endif
