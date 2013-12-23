#ifndef POINT_HPP
#define POINT_HPP
#include "ray.hpp"
#include "intersection.hpp"
#include "types.hpp"
#include "macros.hpp"

class PointObject {
    public:
        PTR_CONSTRUCTOR(PointObject)
        bool intersect(const Ray& ray, Intersection& isect) {
        return false;}
        Point sample() {return m_pos;}
        void renderGL() const;
    private:
        PointObject(const Point& p): m_pos(p) {}
        Point m_pos;
};
#endif
