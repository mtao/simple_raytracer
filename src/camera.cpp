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
    const Vector side = up.cross(lookAt).normalized();

#ifdef USING_OPENMP
#pragma omp parallel for
#endif
    for(int c=0; c < m_film->width(); ++c) {
        Ray ray;
        ray.o = eye;
        double sc = c/width-0.5;
        auto&& dd = lookAt + sc*side;
        for(int r=0; r < m_film->height(); ++r) {

            double sr = r/height-0.5;
            ray.d = (dd + sr * up).normalized();


            m_film->setPixel(c,r,shadeRay(ray));

        }
    }
}
void Camera::run() {
    double width = m_film->width();
    double height = m_film->height();
    Ray ray;
    ray.o = eye;
    const Vector side = up.cross(lookAt).normalized();
    Vector d;

    for(int c=0; c < m_film->width(); ++c) {
        double sc = c/width-0.5;
        auto&& dd = lookAt + sc*side;

        for(int r=0; r < m_film->height(); ++r) {
            double sr = r/height-0.5;
            ray.d = (dd + sr * up).normalized();



            m_film->setPixel(c,r,shadeRay(ray));

        }
    }
}
