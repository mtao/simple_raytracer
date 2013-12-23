#include "mainwindow.hpp"
#include "glwidget.hpp"


MainWindow::MainWindow(): QMainWindow() {
    createMenu();
    createToolbar();
    GLWidget * gl = new GLWidget(this);
    setCentralWidget(gl);
}


void MainWindow::createMenu() {
}

void MainWindow::createToolbar() {
}

GLWidget* MainWindow::glwidget() {
    return static_cast<GLWidget*>(centralWidget());
}

void MainWindow::setScene(const std::shared_ptr<Scene>& scene) {
    qobject_cast<GLWidget*>(centralWidget())->setScene(scene);
}
