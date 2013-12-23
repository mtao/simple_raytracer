#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP
#include "ray.hpp"
#include "intersection.hpp"
#include "phong_material.hpp"
#include "macros.hpp"

class RenderableBase {
    public:
        typedef std::shared_ptr<RenderableBase> Ptr;
        virtual bool intersect(const Ray& ray, Intersection& isect) const = 0;
        virtual Point sample() const = 0;
        virtual void renderGL() const = 0;
        virtual const std::shared_ptr<PhongMaterial>& get_material() const = 0;
        virtual void set_material(const std::shared_ptr<PhongMaterial>&) = 0;
};

template <class T>
class Renderable: public RenderableBase {
    public:
        PTR_CONSTRUCTOR(Renderable<T>)
        bool intersect(const Ray& ray, Intersection& isect) const;
        void renderGL() const {
            return m_obj->renderGL();
        }
        Point sample() const {
            return m_obj->sample();
        }
        const std::shared_ptr<T> & get_object() {return m_obj;}
        const std::shared_ptr<PhongMaterial>& get_material() const {
            return m_mat;
        }
        void set_material(const std::shared_ptr<PhongMaterial>& mat) {
            m_mat = mat;
        }
    private:
        Renderable(const std::shared_ptr<T>& obj, const std::shared_ptr<PhongMaterial>& mat): m_obj(obj), m_mat(mat) {}
        std::shared_ptr<T> m_obj;
        std::shared_ptr<PhongMaterial> m_mat;
};
template <typename T>
bool Renderable<T>::intersect(const Ray& ray, Intersection& isect) const {
    bool succ = m_obj->intersect(ray, isect);
    if( succ && m_mat ) {
        isect.material = m_mat;
    }
    return succ;
}

#endif
