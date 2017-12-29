#ifndef FRACTALWINDOWOGL_H
#define FRACTALWINDOWOGL_H

#include <QtGui/QWidget>
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QGLWidget>

#include "FractalWindow.hpp"

class FractalWindowOGL : public FractalWindow
{
    Q_OBJECT

    public:
        FractalWindowOGL(type fracType, QWidget *parent = 0);
        virtual void initializeGL();
        virtual void resizeGL(int width, int height);
        virtual void paintGL();

    public slots:
        virtual void updateWin();
};

#endif /* ifndef FRACTALWINDOWOGL_H */
