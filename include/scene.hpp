#ifndef SCENE_HPP
#define SCENE_HPP
#include <memory>
#include <vector>

#include "ray.hpp"
#include "intersection.hpp"
#include "renderable.hpp"
#include "phong_material.hpp"
#include "phong_light.hpp"
#include "macros.hpp"

class SceneNode;
class TransformationSceneNode;

class SceneNode {
    public:
        PTR_CONSTRUCTOR(SceneNode)
        bool intersect(const Ray& ray, Intersection& isect) const;
        template <typename T>
            void add(const std::shared_ptr<T>& obj, const std::shared_ptr<PhongMaterial>& mat = 0);
        void addRenderable(const std::shared_ptr<RenderableBase>& r);

        std::shared_ptr<SceneNode> addNode();
        std::shared_ptr<TransformationSceneNode> addTransformNode();

        virtual void renderGL() const;

        const std::vector<std::shared_ptr<RenderableBase> >& get_renderables() const {return m_renderables;}

        Point sample() const;
        std::vector<std::shared_ptr<RenderableBase> >& get_renderables() {return m_renderables;}
    protected:

        SceneNode() {}
    private:
        std::vector<std::shared_ptr<RenderableBase> > m_renderables;

};

class TransformationSceneNode: public SceneNode {
    public:
        PTR_CONSTRUCTOR(TransformationSceneNode)
        TransformationSceneNode(TransformationSceneNode&&) = default;
        TransformationSceneNode(const AffineTransform& t);
        bool intersect(const Ray& ray, Intersection& isect) const;
        void set_transform(const AffineTransform& t);
        const AffineTransform& get_transform() const {return m_transform;}
        template <typename T>
            void apply_transform(const T& A);
        Point sample() const;
        virtual void renderGL() const;
    protected:
        TransformationSceneNode() = default;
    private:
        AffineTransform m_transform = AffineTransform::Identity();
        AffineTransform m_invtransform = AffineTransform::Identity();
};


class Scene: public SceneNode {
    public:
        PTR_CONSTRUCTOR(Scene)
        const std::vector<PhongLight>& get_lights() const {return m_lights;}
        void set_lights(const std::vector<PhongLight>& lights) {m_lights = lights;}

        template <typename T>
            void add_light(const std::shared_ptr<T>& obj, const std::shared_ptr<PhongMaterial>& mat);
    protected:
        Scene() {}
    private:
        std::vector<PhongLight> m_lights;
};

template <typename T>
void SceneNode::add(const std::shared_ptr<T>& obj, const std::shared_ptr<PhongMaterial>& mat) {
    m_renderables.push_back(Renderable<T>::create(obj, mat));
}

template <typename T>
void TransformationSceneNode::apply_transform(const T& A) {
    m_transform = m_transform * A;
    m_invtransform = A.inverse() * m_invtransform;
}

template <typename T>
void Scene::add_light(const std::shared_ptr<T>& obj, const std::shared_ptr<PhongMaterial>& mat) {
    m_lights.push_back(PhongLight(Renderable<T>::create(obj, mat)));
}

#endif
