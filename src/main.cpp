#include "film.hpp"
#include "sphere.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "point.hpp"
#include <time.h>
#include <iostream>

int main() {
    auto root = std::make_shared<Scene>();
    auto light = std::make_shared<PointObject>(Point(2,2,-4));

    auto white_mat = std::make_shared<PhongMaterial>(Color(1,1,1),Color(1,1,1),Color(1,1,1),1.0);
    root->add_light(light, white_mat);

    auto red_mat = std::make_shared<PhongMaterial>(Color(0.2,0,0),Color(0.1,.1,.1),Color(.1,.1,.1),1.0);
    auto purple_mat = std::make_shared<PhongMaterial>(Color(0.4,0.4,0),Color(0.1,.1,.1),Color(.1,.1,.1),1.0);
    root->add(std::make_shared<Sphere>(), red_mat);

    auto translate = std::make_shared<TransformationSceneNode>();
    translate->set_transform(AffineTransform::Identity()*Eigen::Translation<double,3>(1,0,0));

    translate->add(std::make_shared<Sphere>(), purple_mat);
    root->add(translate);

    root->set_transform(AffineTransform::Identity()*Eigen::Translation<double,3>(0,0,-5));
    auto film = std::make_shared<Film>(300,300);
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
