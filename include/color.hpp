#ifndef COLOR_HPP
#define COLOR_HPP
#include "types.hpp"
#include <QtGui/QRgb>

struct Color: public Vector3 {
    Color() {}
    Color(const Vector3& v): Vector3(v) {}
    Color(double r, double g, double b): Vector3(r,g,b) {}
    Color& operator=(const Vector3& v) {Vector3::operator=(v); return *this;}
    double& r() {return (*this)(0);}
    double& g() {return (*this)(1);}
    double& b() {return (*this)(2);}
    double r()const {return (*this)(0);}
    double g()const {return (*this)(1);}
    double b()const {return (*this)(2);}
    operator unsigned int() {
        return qRgb(255*r(),255*g(),255*b());
    }
};
#endif
