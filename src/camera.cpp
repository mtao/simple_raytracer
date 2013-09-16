#include "camera.hpp"

Camera::Camera(const std::shared_ptr<Scene>& scene,const std::shared_ptr<Film>& film): m_film(film), m_scene(scene) {
}
QRgb Camera::shadeRay(const Ray& r) const {
            Intersection isect;
            if(m_scene->intersect(r,isect)) {
                Color c(Color::Zero());
                for(auto&& l: m_scene->get_lights()) {
                    c += l.shade(r,isect);
                }
                return c;
            } else {
                return qRgb(0,0,0);
            }
}

void Camera::run_omp() {
    double width = m_film->width();
    double height = m_film->height();

#pragma omp parallel for
    for(int c=0; c < m_film->width(); ++c) {
        Ray ray;
        ray.o = Point(0,0,-1);
        for(int r=0; r < m_film->height(); ++r) {
            Vector d;
            d(0) = c/width-0.5;
            d(1) = r/height-0.5;
            d(2) = 1.0;

            ray.d = d.normalized();


            m_film->setPixel(r,c,shadeRay(ray));

        }
    }
}
void Camera::run() {
    double width = m_film->width();
    double height = m_film->height();
    Ray ray;
    ray.o = Point(0,0,-1);
    Vector d;
    d(2) = 1.0;

    for(int c=0; c < m_film->width(); ++c) {
        d(0) = c/width-0.5;
        for(int r=0; r < m_film->height(); ++r) {
            d(1) = r/height-0.5;

            ray.d = d.normalized();


            m_film->setPixel(r,c,shadeRay(ray));

        }
    }
}
