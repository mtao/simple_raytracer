#include "scene.hpp"

bool SceneNode::intersect(const Ray& ray, Intersection& isect) const {
    bool hasIntersection;
    for(const RenderableBase& renderable: m_renderables) {
        hasIntersection |= renderable.intersect(ray,isect);
    }
    return hasIntersection;
}

bool TransformationSceneNode::intersect(const Ray& ray, Intersection& isect) const {
    Ray r = ray.apply(this->get_transform());
    bool hasIntersection;
    for(const RenderableBase& renderable: this->get_renderables()) {
        hasIntersection |= renderable.intersect(r,isect);
    }
    if(hasIntersection) {
        isect.normal = (m_invtransform.linear().transpose() * isect.normal).normalized();
    }
    return hasIntersection;
}
