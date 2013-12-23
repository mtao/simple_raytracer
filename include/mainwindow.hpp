#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP


#include <QtWidgets/QMainWindow>
#include <memory>
#include "scene.hpp"

class GLWidget;

class MainWindow: public QMainWindow {
    Q_OBJECT
    public:
        MainWindow();
    private:
        void createMenu();
        void createToolbar();
        GLWidget* glwidget();
    public slots:
        void setScene(const std::shared_ptr<Scene>& scene);


};
#endif
