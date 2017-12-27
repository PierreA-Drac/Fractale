#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QGLFormat>
#include <QtOpenGL/QGLShader>
#include <QtOpenGL/QGLShaderProgram>
//#include <qt5/QtGui/QOpenGLFunctions>


class RenderWidget : public QGLWidget//, protected QOpenGLFunctions
{
  Q_OBJECT

public:
    RenderWidget(QWidget* widget = nullptr);
    ~RenderWidget();

public slots:
    void loadJuliaFractal();
    void loadMandelbrotFractal();

private:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    virtual void mousePressEvent(QMouseEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);

    QGLShader* _vertexShader;
    QGLShaderProgram _shaderProgram;

    int _iterations;

    QPointF _centre;
    float _scale;
};

#endif // GLWIDGET_H
