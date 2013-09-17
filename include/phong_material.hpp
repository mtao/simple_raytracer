#ifndef PHONG_MATERIAL_HPP
#define PHONG_MATERIAL_HPP
#include "color.hpp"


struct PhongMaterial {
    PhongMaterial(const Color& d, const Color& s, const Color& a, double spec = 1.0)
        : d(d), s(s), a(a), spec(spec) {}
    Color d,s,a;
    double spec;
};

#endif
