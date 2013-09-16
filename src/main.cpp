#include "film.hpp"
#include "sphere.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "point.hpp"
//#include "scene_graph_optimizer.hpp"
#include <time.h>
#include <iostream>

int main() {
    auto root = std::make_shared<Scene>();
    auto instance = root->addNode();
    auto view_trans_node = instance->addTransformNode();
    view_trans_node->set_transform(AffineTransform::Identity()*Eigen::Translation<double,3>(-0.5,0,-5));
    auto light = std::make_shared<PointObject>(Point(0,0,-4));

    auto white_mat = std::make_shared<PhongMaterial>(Color(1,1,1),Color(1,1,1),Color(1,1,1),1.0);
    root->add_light(light, white_mat);

    auto red_mat = std::make_shared<PhongMaterial>(Color(0.2,0,0),Color(0.1,.1,.1),Color(.1,.1,.1),1.0);
    auto purple_mat = std::make_shared<PhongMaterial>(Color(0.4,0.4,0),Color(0.1,.1,.1),Color(.1,.1,.1),1.0);
    view_trans_node->add(std::make_shared<Sphere>(), red_mat);

    auto translate = view_trans_node->addTransformNode();
    translate->set_transform(AffineTransform::Identity()*Eigen::Translation<double,3>(1,0,0));

    translate->add(std::make_shared<Sphere>(), purple_mat);

    auto tn = root->addTransformNode();
    tn->set_transform(AffineTransform::Identity() * Eigen::Scaling(1.0,2.0,0.5) * Eigen::Translation<double,3>(0,-2,3));
    tn->add(instance);
    auto tn2 = root->addTransformNode();
    tn2->set_transform(AffineTransform::Identity() * Eigen::Scaling(1.0,2.0,0.5) * Eigen::Translation<double,3>(0,2,3));
    tn2->add(instance);

    auto film = std::make_shared<Film>(3000,3000);
    Camera c(root,film);


    time_t start;
    time_t end;
    /*
    time(&start);
    c.run_omp();
    time(&end);
    std::cout << "omp: " << difftime(end,start) << std::endl;
    */

    time(&start);
    c.run();
    time(&end);
    std::cout << "normal: " << difftime(end,start) << std::endl;
    film->save("test.png");


}
