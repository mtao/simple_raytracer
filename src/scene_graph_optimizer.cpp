#include "scene_graph_optimizer.hpp"


Scene::Ptr SceneGraphOptimizer::run(const Scene::Ptr& s) {
    AffineTransform T = AffineTransform::Identity();
    std::shared_ptr<PhongMaterial> mat = 0;
    *scene = *s;
    scene->get_renderables().clear();
    run(*dynamic_cast<SceneNode*>(s.get()),T,mat);

    return scene;

}



void SceneGraphOptimizer::run(SceneNode& n, const AffineTransform& T, const PhongMaterial::Ptr& curMat) {
    for(auto&& r: n.get_renderables()) {
        recast_and_run(r,T,curMat);
    }
}

void SceneGraphOptimizer::run(TransformationSceneNode& n, const AffineTransform& T, const PhongMaterial::Ptr& curMat) {
    run(*dynamic_cast<SceneNode*>(&n), n.get_transform() * T, curMat);
}

void SceneGraphOptimizer::recast_and_run(const RenderableBase::Ptr& r, const AffineTransform& T, const PhongMaterial::Ptr& curMat) {
    auto&& r_type = typeid(*r);

    auto mat = curMat;
    if(r->get_material()) {
        mat = r->get_material();
    }
    if(r_type == typeid(Renderable<TransformationSceneNode>) ) {
        run(*(static_cast<Renderable<TransformationSceneNode>*>(r.get())->get_object()),T,mat);
    } else if (r_type == typeid(Renderable<SceneNode>) ) {
        run(*(static_cast<Renderable<SceneNode>*>(r.get())->get_object()),T,mat);
    } else {
        add(r,T,mat);

    }
}


void SceneGraphOptimizer::add(const RenderableBase::Ptr& r, const AffineTransform& T, const PhongMaterial::Ptr& curMat) {
    auto t = TransformationSceneNode::create(T);
    t->addRenderable(r);
    scene->add(t,curMat);
}
