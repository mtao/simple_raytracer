#include "scene.hpp"
#include <cstdlib>
#ifdef USING_OPENGL
#include <GL/glew.h>
#include <Eigen/OpenGLSupport>
#endif

bool SceneNode::intersect(const Ray& ray, Intersection& isect) const {
    bool hasIntersection = false;
    for(const RenderableBase::Ptr& renderable: this->get_renderables()) {
        hasIntersection |= renderable->intersect(ray,isect);
    }
    return hasIntersection;
}

void SceneNode::addRenderable(const RenderableBase::Ptr& r) {
    m_renderables.push_back(r);
}

SceneNode::Ptr SceneNode::addNode() {
    auto n = SceneNode::create();
    this->add(n);
    return n;
}
TransformationSceneNode::Ptr SceneNode::addTransformNode() {
    auto n = TransformationSceneNode::create();
    this->add(n);
    return n;
}

void SceneNode::renderGL() const {
    for(auto&& r: m_renderables) {
        r->renderGL();
    }
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
    for(const RenderableBase::Ptr& renderable: this->get_renderables()) {
        hasIntersection |= renderable->intersect(r,isect);
    }
    if(hasIntersection) {
        isect.normal = (m_invtransform.linear().transpose() * isect.normal).normalized();
    }
    return hasIntersection;
}
TransformationSceneNode::TransformationSceneNode(const AffineTransform& t) {
    set_transform(t);
}
void TransformationSceneNode::set_transform(const AffineTransform& t) {
    m_transform = t;
    m_invtransform = t.inverse();
}


void TransformationSceneNode::renderGL() const {
#ifdef USING_OPENGL
    glPushMatrix();
    glMultMatrix(m_transform);

    for(auto&& r: get_renderables()) {
        r->renderGL();
    }
    glPopMatrix();
#endif
}
