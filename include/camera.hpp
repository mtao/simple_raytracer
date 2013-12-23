#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "scene.hpp"
#include "film.hpp"
#include <memory>
#include <QtGui/QImage>
class Camera {
    public:
        Camera(const std::shared_ptr<Scene>& scene, const std::shared_ptr<Film>& film);
        void run();
        void run_omp();
        QRgb shadeRay(const Ray& r) const;
    private:
        std::shared_ptr<Film> m_film;
        std::shared_ptr<Scene> m_scene;
        Point eye = Point(0,0,0);
        Vector lookAt = Vector(0,0,1);
        Vector up = Vector(0,1,0);
};

#endif
