#include "phong_light.hpp"

Color PhongLight::shade(const Ray& r, const Intersection& isect) const {

        auto&& mymat = m_renderable->get_material();
        auto&& imat = isect.material;
        auto&& a = imat->a;
        auto&& d = imat->d;
        auto&& s = imat->s;
        auto&& spec = imat->spec;
        Vector in = (m_renderable->sample() - isect.point).normalized();
        Vector out = -r.d;
        auto&& normal = isect.normal;



        auto&& R = 2 * in.dot(normal) * normal - in;
        auto&& amb = 
            a.cwiseProduct(mymat->a) ;
        double n_l_dot = in.dot(normal);
        if(n_l_dot < 0) {
            return Color(amb);
        }
        auto&& diff = 
            + n_l_dot * d.cwiseProduct(mymat->d);
        auto&& specu = 
            + std::max(0.0,std::pow(R.dot(out),spec)) * s.cwiseProduct(mymat->s);
        return  Color(amb + diff + specu);
}
