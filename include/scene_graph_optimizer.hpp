#ifndef SCENE_GRAPH_OPTIMIZER_HPP
#define SCENE_GRAPH_OPTIMIZER_HPP
#include "scene.hpp"
class SceneGraphOptimizer {
    public:
        SceneGraphOptimizer(): scene(Scene::create()) {}
        std::shared_ptr<Scene> run(const Scene::Ptr& s);
        void run(SceneNode& n, const AffineTransform& T, const PhongMaterial::Ptr& curMat);
        void run(TransformationSceneNode& n, const AffineTransform& T, const PhongMaterial::Ptr& curMat);
        void recast_and_run(const std::shared_ptr<RenderableBase>& r, const AffineTransform& T, const PhongMaterial::Ptr& curMat);
        void add(const std::shared_ptr<RenderableBase>& r, const AffineTransform& T, const PhongMaterial::Ptr& curMat);
    private:
        Scene::Ptr scene;

};
#endif
