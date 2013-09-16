#include "film.hpp"
#include "ray.hpp"
#include "intersection.hpp"

Film::Film(int rows, int cols): m_img(rows,cols,QImage::Format_ARGB32) {
}



void Film::save(const QString & filename) {
    m_img.save(filename);
}
