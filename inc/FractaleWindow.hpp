#ifndef FRACTALEWINDOW_H
#define FRACTALEWINDOW_H

#include "FractaleGLWidget.hpp"
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QGLShader>
#include <QtOpenGL/QGLShaderProgram>
#define BLACK_WHITE 0
#define COLOR 1
#define MANDELBROT 0
#define JULIA 1

class FractaleWindow : public FractaleGLWidget
{
    Q_OBJECT
    
    private:
        QGLShader* _vertexShader;
        QGLShaderProgram _shaderProgram;

        int _iterations;

        QPointF _centre;
        float _scale;
        bool _coul;
        bool _fracType;

    public:
        FractaleWindow(bool fracType, bool coul, QWidget *parent = 0);
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void MandelbrotFractal();
        void JuliaFractal();
        void keyPressEvent(QKeyEvent *keyEvent);
};

#endif /* ifndef FRACTALEWINDOW_H */
