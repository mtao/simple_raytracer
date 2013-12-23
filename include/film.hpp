#ifndef FILM_HPP
#define FILM_HPP

#include <memory>
#include <QtGui/QImage>
#include "macros.hpp"
class Film {
    public:
        PTR_CONSTRUCTOR(Film)
        Film(int rows, int cols);
        void save(const QString& filename = "image.png");
        int width() const {return m_img.width();}
        int height() const {return m_img.height();}
        //TODO: update this to something fancier / nicer
        void setPixel(int i, int j, uint rgba) {m_img.setPixel(i,j,rgba);}
    private:
        QImage m_img;
};

#endif
