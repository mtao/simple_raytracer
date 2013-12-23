#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "ray.hpp"
#include "intersection.hpp"

class Sphere {
    public:
    bool intersect(const Ray& ray, Intersection& isect) const;
    Point sample() const;
    void renderGL() const;
};
#endif
