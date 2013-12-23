#include "sphere.hpp"
#include <cmath>
#include <iostream>
#ifdef USING_OPENGL
#include <GL/glew.h>
#include <Eigen/OpenGLSupport>
#endif
bool Sphere::intersect(const Ray& ray, Intersection& isect) const {
    const Vector& d = ray.d;
    auto&& o = ray.o.topRows<3>();
    double A,B,C,D;
    A = d.squaredNorm();
    B = o.dot(d);
    C = o.dot(o) - 1.0;
    D = B*B-A*C;
    if(D >= 0) {
        double t1 = -(B+std::sqrt(D))/A;
        double t2 = (-B+std::sqrt(D))/A;
        double t = std::min(t1*(t1>0),t2*(t2>0));
        if(isect.none || t < isect.time) {
            Point p = ray.eval(t);
            Vector n = p.topRows<3>().normalized();
            isect.set(t,n);
            return true;
        }
    }


    return false;
}

Point Sphere::sample() const {
    return Point::Random().normalized();

}


void Sphere::renderGL() const {
#ifdef USING_OPENGL
    glBegin(GL_POINTS);
    glVertex(Vector());
    glEnd();
#endif
}
