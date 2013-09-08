#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "ray.hpp"
#include "intersection.hpp"

class Sphere {
    bool intersect(const Ray& ray, Intersection& isect) const;
};
#endif
