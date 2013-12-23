#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "ray.hpp"
#include "intersection.hpp"
#include "macros.hpp"

class Sphere {
    public:
        PTR_CONSTRUCTOR(Sphere)
    bool intersect(const Ray& ray, Intersection& isect) const;
    Point sample() const;
    void renderGL() const;
    protected:
    Sphere() = default;
};
#endif
