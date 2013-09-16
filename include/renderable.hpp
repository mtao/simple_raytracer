#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP
#include <memory>
#include "ray.hpp"
#include "intersection.hpp"
#include "phong_material.hpp"

class RenderableBase {
    public:
        virtual bool intersect(const Ray& ray, Intersection& isect) const = 0;
        virtual Point sample() const = 0;
        virtual const std::shared_ptr<PhongMaterial>& get_material() const = 0;
};
template <class T>
class Renderable: public RenderableBase {
    public:
        Renderable(const std::shared_ptr<T>& obj, const std::shared_ptr<PhongMaterial>& mat): m_obj(obj), m_mat(mat) {}
        bool intersect(const Ray& ray, Intersection& isect) const {
            bool succ = m_obj->intersect(ray, isect);
            if( succ && m_mat ) {
                isect.material = m_mat;
            }
            return succ;
        }
        Point sample() const {
            return m_obj->sample();
        }
        const std::shared_ptr<PhongMaterial>& get_material() const {
            return m_mat;
        }
    private:
        std::shared_ptr<T> m_obj;
        std::shared_ptr<PhongMaterial> m_mat;
};

#endif
