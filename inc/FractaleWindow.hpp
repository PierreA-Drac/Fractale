#ifndef FRACTALEWINDOW_H
#define FRACTALEWINDOW_H

#include "FractaleGLWidget.hpp"
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QGLShader>
#include <QtOpenGL/QGLShaderProgram>

class FractaleWindow : public FractaleGLWidget
{
    Q_OBJECT
    
    private:
        QGLShader* _vertexShader;
        QGLShaderProgram _shaderProgram;

        int _iterations;

        QPointF _centre;
        float _scale;

    public:
        explicit FractaleWindow(QWidget *parent = 0);
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void loadMandelbrotFractal();
        void keyPressEvent(QKeyEvent *keyEvent);
};

#endif /* ifndef FRACTALEWINDOW_H */
