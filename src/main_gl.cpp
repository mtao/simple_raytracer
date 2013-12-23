#include "scene.hpp"
#include <QtWidgets/QApplication>
#include "mainwindow.hpp"
#include "film.hpp"
#include "sphere.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "point.hpp"
#include "scene_graph_optimizer.hpp"


int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
    MainWindow mainwindow;
    mainwindow.show();

    //Root of scene
    auto root = std::make_shared<Scene>();

    //Create a point object at 0,0,-4 to add a light source to the scene.  It has a white material
    auto light = std::make_shared<PointObject>(Point(0,0,-4));
    //Declare the color of the light in a phong sense
    auto white_mat = std::make_shared<PhongMaterial>(Color(1,1,1),Color(1,1,1),Color(1,1,1));
    //Add light to list of lights.  Can also use other objects / instances as the source but currently they won't be sampled properly
    root->add_light(light, white_mat);

    //Materials for use later on
    auto red_mat = std::make_shared<PhongMaterial>(Color(0.4,0,0),Color(0.1,.1,.1),Color(.1,.1,.1),1.0);
    auto blue_mat = std::make_shared<PhongMaterial>(Color(0.0,0.0,0.4),Color(0.1,.1,.1),Color(.1,.1,.1),1.0);

    //Creating a new node that will be used for instancing
    auto instance = std::make_shared<SceneNode>();
    //Add nodes to transform the objects up and down + add the objects as leaves in scene dag
    auto up = instance->addTransformNode();
    up->apply_transform(Eigen::Translation<double,3>(0.0, 0.5,0.0));
    up->add(std::make_shared<Sphere>(), red_mat);

    auto down = instance->addTransformNode();
    down->apply_transform(Eigen::Translation<double,3>(0.0,-0.5,0.0));
    down->add(std::make_shared<Sphere>(), blue_mat);






    //Root transform for all nodes in scene, it's a child of the root
    auto view_trans_node = root->addTransformNode();
    AffineTransform base = AffineTransform::Identity();
    base.translate(Vector(0,0,-5));
    view_trans_node->set_transform(base);

    //Add instance of node at root
    view_trans_node->add(instance);


    //Add transform nodes to add spheres to the left and right, with scaling and rotations
    auto tn = view_trans_node->addTransformNode();
    tn->apply_transform(Eigen::Scaling(2.0,1.0,0.5) * Eigen::AngleAxis<double>(-3.14159,Vector(0,0,1))  * Eigen::Translation<double,3>(-2,0,-2));
    tn->add(instance);

    auto tn2 = view_trans_node->addTransformNode();
    tn2->apply_transform(Eigen::Scaling(2.0,1.0,0.5) * Eigen::AngleAxis<double>(3.14159,Vector(0,0,1))  * Eigen::Translation<double,3>(2,0,-2));
    tn2->add(instance);


    mainwindow.setScene(root);
    return app.exec();
}
