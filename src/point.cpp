
#include "point.hpp"
#ifdef USING_OPENGL
#include <GL/glew.h>
#include <Eigen/OpenGLSupport>
#endif

void PointObject::renderGL() const {
#ifdef USING_OPENGL
    glBegin(GL_POINTS);
    glVertex(Vector(m_pos));
    glEnd();
#endif
}
