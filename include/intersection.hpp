#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP
#include "types.hpp"
#include "phong_material.hpp"
#include <memory>

struct Intersection {
    double time = 0.0;
    std::shared_ptr<PhongMaterial> material = 0;
    Vector normal;
    Point point;
    bool none = true;
    void set(double t, const Vector& n) {
        none = false;
        time = t;
        normal = n;
    }
    operator bool() {
        return !none;
    }
};

#endif
