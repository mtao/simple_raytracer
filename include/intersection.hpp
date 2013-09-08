#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

struct Intersection {
    double time = 0.0;
    Vector normal;
    Point point;
    bool none = true;
    void set(double t, const Vector& n) {
        none = false;
        time = t;
        normal = n;
    }
};

#endif
