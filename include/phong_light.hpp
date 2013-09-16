#ifndef PHONG_LIGHT_HPP
#define PHONG_LIGHT_HPP
#include "color.hpp"
#include "ray.hpp"
#include "renderable.hpp"
#include <memory>

class PhongLight {
    public:
        PhongLight(const std::shared_ptr<RenderableBase> & r): m_renderable(r) {}
        Color shade(const Ray& r, const Intersection& isect) const;
    private:
        std::shared_ptr<RenderableBase> m_renderable;
};
#endif
