#include "scene.hpp"
#include <cstdlib>

bool SceneNode::intersect(const Ray& ray, Intersection& isect) const {
    bool hasIntersection = false;
    for(const std::shared_ptr<RenderableBase>& renderable: this->get_renderables()) {
        hasIntersection |= renderable->intersect(ray,isect);
    }
    return hasIntersection;
}

//TODO: Naive scheme...
Point SceneNode::sample() const {
    return m_renderables[std::rand() % m_renderables.size()]->sample();
}
//TODO: Naive scheme...
Point TransformationSceneNode::sample() const {
    return m_invtransform * get_renderables()[std::rand() % get_renderables().size()]->sample();
}

bool TransformationSceneNode::intersect(const Ray& ray, Intersection& isect) const {
    Ray r = ray.apply(this->get_transform());
    bool hasIntersection = false;
    for(const std::shared_ptr<RenderableBase>& renderable: this->get_renderables()) {
        hasIntersection |= renderable->intersect(r,isect);
    }
    if(hasIntersection) {
        isect.normal = (m_invtransform.linear().transpose() * isect.normal).normalized();
    }
    return hasIntersection;
}
