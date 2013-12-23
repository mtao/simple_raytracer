#ifndef PHONG_MATERIAL_HPP
#define PHONG_MATERIAL_HPP
#include "color.hpp"
#include "macros.hpp"


struct PhongMaterial {
    PTR_CONSTRUCTOR(PhongMaterial)
    PhongMaterial(const Color& d, const Color& s, const Color& a, double spec = 1.0)
    : d(d), s(s), a(a), spec(spec) {}
    PhongMaterial(const PhongMaterial& other) = default;
    PhongMaterial(PhongMaterial&& other) = default;
    PhongMaterial& operator=(const PhongMaterial& other) = default;
    PhongMaterial& operator=(PhongMaterial&& other) = default;
    Color d,s,a;
    double spec;

};

#endif
