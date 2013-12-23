#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP
#include <QtOpenGL/QGLWidget>
#include "scene.hpp"

class GLWidget: public QGLWidget {
    Q_OBJECT
    public:
        GLWidget(QWidget * parent);
        void setScene(const std::shared_ptr<Scene>& scene);
    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);

    private:
        std::shared_ptr<Scene> m_scene;
};
#endif
