#ifndef SCENE_HPP
#define SCENE_HPP
#include <memory>
#include <vector>

#include "ray.hpp"
#include "intersection.hpp"
#include "renderable.hpp"
#include "phong_material.hpp"
#include "phong_light.hpp"

class SceneNode {
    public:
        SceneNode() {}
        bool intersect(const Ray& ray, Intersection& isect) const;
        /*
        template <typename T>
            void add(const Renderable<T>& obj) {
                m_renderables.push_back(obj);
            }
            */
        //template <typename T, typename U>
        template <typename T>
            void add(const std::shared_ptr<T>& obj, const std::shared_ptr<PhongMaterial>& mat = 0) {
                m_renderables.push_back(std::make_shared<Renderable<T> >(obj, mat));
            }

        const std::vector<std::shared_ptr<RenderableBase> >& get_renderables() const {return m_renderables;}

        Point sample() const;
    private:
        std::vector<std::shared_ptr<RenderableBase> > m_renderables;

};

class TransformationSceneNode: public SceneNode {
    public:
        bool intersect(const Ray& ray, Intersection& isect) const;
        void set_transform(const AffineTransform& t) {
            m_transform = t;
            m_invtransform = t.inverse();
        }
        const AffineTransform& get_transform() const {return m_transform;}
        Point sample() const;
    private:
        AffineTransform m_transform = AffineTransform::Identity();
        AffineTransform m_invtransform = AffineTransform::Identity();
};


class Scene: public TransformationSceneNode {
    public:
        const std::vector<PhongLight>& get_lights() const {return m_lights;}

        template <typename T>
            void add_light(const std::shared_ptr<T>& obj, const std::shared_ptr<PhongMaterial>& mat) {
                m_lights.push_back(PhongLight(std::make_shared<Renderable<T> >(obj, mat)));
            }
        //template <typename T>
        //void add_light(const std::shared_ptr<T>& l) {
        //    m_lights.push_back(std::make_shared<Light<T> >(l));
        //}
    private:
        std::vector<PhongLight> m_lights;
};




#endif
