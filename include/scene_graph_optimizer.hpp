#ifndef SCENE_GRAPH_OPTIMIZER_HPP
#define SCENE_GRAPH_OPTIMIZER_HPP
#include "scene.hpp"
class SceneGraphOptimizer {
    public:
        SceneGraphOptimizer(): scene(std::make_shared<Scene>()) {}
        std::shared_ptr<Scene> run(const std::shared_ptr<Scene>& s);
        void run(SceneNode& n, const AffineTransform& T, const std::shared_ptr<PhongMaterial>& curMat);
        void run(TransformationSceneNode& n, const AffineTransform& T, const std::shared_ptr<PhongMaterial>& curMat);
        void recast_and_run(const std::shared_ptr<RenderableBase>& r, const AffineTransform& T, const std::shared_ptr<PhongMaterial>& curMat);
        void add(const std::shared_ptr<RenderableBase>& r, const AffineTransform& T, const std::shared_ptr<PhongMaterial>& curMat);
    private:
        std::shared_ptr<Scene> scene;

};
#endif
