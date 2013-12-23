#include <GL/glew.h>
#include "glwidget.hpp"

GLWidget::GLWidget(QWidget * parent): QGLWidget(parent) {
}

void GLWidget::setScene(const std::shared_ptr<Scene>& scene) {
    m_scene = scene;
}

void GLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    qglClearColor(QColor(0,0,0));
}

void GLWidget::resizeGL(int w, int h) {
    qreal ratio = qreal(w)/h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1,1,1);
    glBegin(GL_POINTS);
    glVertex3f(0,0,0);
    glEnd();
    if(m_scene) {
        m_scene->renderGL();
    }
}
