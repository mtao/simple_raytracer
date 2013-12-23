#ifndef POINT_HPP
#define POINT_HPP
#include "ray.hpp"
#include "intersection.hpp"
#include "types.hpp"

class PointObject {
    public:
        PointObject(const Point& p): m_pos(p) {}
        bool intersect(const Ray& ray, Intersection& isect) {
        return false;}
        Point sample() {return m_pos;}
        void renderGL() const;
    private:
        Point m_pos;
};
#endif
