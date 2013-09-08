#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP
#include <memory>
#include "ray.hpp"
#include "intersection.hpp"

class RenderableBase {
    public:
        virtual bool intersect(const Ray& ray, Intersection& isect) const = 0;
};

template <class T>
class Renderable: public RenderableBase {
    public:
        Renderable(const std::shared_ptr<T>& obj): m_obj(obj) {}
        bool intersect(Ray& ray, Intersection& isect) const {
            return m_obj->intersect(ray, time);
        }
    private:
        std::shared_ptr<T> m_obj;
};

#endif
