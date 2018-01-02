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
#define xmin -2.0
#define xmax 1.0
#define ymin -1.5
#define ymax 1.5

class FractaleWindow : public FractaleGLWidget
{
    Q_OBJECT
    
    private:
        QGLShader* _vertexShader;
        QGLShaderProgram _shaderProgram;

        int _iterations;

        QPointF _centre;
        float _scale;
        bool _fracType;
        bool _coul;
        
    public:
        FractaleWindow(bool fracType, bool coul, QWidget *parent = 0);
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void MandelbrotFractal();
        void JuliaFractal();
        void keyPressEvent(QKeyEvent *keyEvent);
        void releaseShaderProg();
};

#endif /* ifndef FRACTALEWINDOW_H */
