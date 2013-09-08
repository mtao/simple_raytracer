#ifndef SCENE_HPP
#define SCENE_HPP
#include <memory>
#include <vector>

#include "ray.hpp"
#include "intersection.hpp"
#include "renderable.hpp"

class SceneNode {
    public:
        SceneNode() {}
        bool intersect(const Ray& ray, Intersection& isect) const;
        template <typename T>
            void add(const Renderable<T>& obj) {
                m_renderables.push_back(obj);
            }

        const std::vector<RenderableBase>& get_renderables() const {return m_renderables;}
    private:
        std::vector<RenderableBase> m_renderables;

};

class TransformationSceneNode: public SceneNode {
    public:
        bool intersect(const Ray& ray, Intersection& isect) const;
        void set_transform(const AffineTransform& t) {
            m_transform = t;
            m_invtransform = t.inverse();
        }
        const AffineTransform& get_transform() const {return m_transform;}
    private:
        AffineTransform m_transform = AffineTransform::Identity();
        AffineTransform m_invtransform = AffineTransform::Identity();
};


class Scene {
    public:

    private:
        TransformationSceneNode m_root;
};




#endif
