#ifndef FRACTALEWINDOW_H
#define FRACTALEWINDOW_H

#include "FractaleGLWidget.hpp"

class FractaleWindow : public FractaleGLWidget
{
    Q_OBJECT

    public:
        explicit FractaleWindow(QWidget *parent = 0);
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
};

#endif /* ifndef FRACTALEWINDOW_H */
