/**
 * @file FractalWindowOGL.cpp
 * @brief Fenêtre d'une fractale rendu avec OpenGL.
 *
 * Implémentation de la classe de la fenêtre d'une fractale rendu avec OpenGL.
 */

#include "FractalWindowOGL.hpp"

#include <stdexcept>
#include <string>

#include <QtCore/QDebug>
#include "QtCore/QString"

FractalWindowOGL::FractalWindowOGL(type fracType, bool coul, QWidget *parent) 
    : FractalWindow(fracType, FractalWindow::OPENGL, coul, parent, 60)
    , center(0.f, 0.f) , scale(1.f)
{
}

void FractalWindowOGL::initializeGL()
{
    /* Initialisation d'OpenGL. */
    qglClearColor(QColor(Qt::black));
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    /* Initialisation des shaders. */
    std::string fragShader;
    if (fracType == MANDELBROT)
        fragShader = "shaders/fragmentShaderMandelbrot.fsh";
    else if (fracType == JULIA)
        fragShader = "shaders/fragmentShaderJulia.fsh";

    shaderProgram = new QGLShaderProgram(context(), this);
    if (!shaderProgram->addShaderFromSourceFile(QGLShader::Vertex,
                "shaders/vertexShader.vsh")
            || !shaderProgram->addShaderFromSourceFile(QGLShader::Fragment,
                fragShader.data())
            || !shaderProgram->link()) {
        throw std::runtime_error("Shader initialization failed");
    }
}

void FractalWindowOGL::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void FractalWindowOGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (n <= nMax)
        n++;

    shaderProgram->bind();
    shaderProgram->setUniformValue("n_max", n);
    shaderProgram->setUniformValue("b_color", coul);
    shaderProgram->setUniformValue("c", c);
    shaderProgram->setUniformValue("z_max", zMax * 2);
    shaderProgram->setUniformValue("scale", scale);
    shaderProgram->setUniformValue("center", center);

    const GLfloat quadVertices[] =
    {
        -1.f, -1.f,
        1.f, -1.f,
        1.f, 1.f,
        -1.f, 1.f
    };

    const GLfloat textureCoordinates[] =
    {
        0.f, 0.f,
        1.f, 0.f,
        1.f, 1.f,
        0.f, 1.f
    };

    shaderProgram->setAttributeArray("vertex", quadVertices, 2);
    shaderProgram->enableAttributeArray("vertex");
    shaderProgram->setAttributeArray("texture_in", textureCoordinates, 2);
    shaderProgram->enableAttributeArray("texture_in");

    glDrawArrays(GL_QUADS, 0, 4);

    shaderProgram->disableAttributeArray("vertex");
    shaderProgram->disableAttributeArray("texture_in");
    shaderProgram->release();
}

void FractalWindowOGL::updateWin()
{
    updateGL();
}

void FractalWindowOGL::zoomUp()
{
    scale *= 0.9f;
}

void FractalWindowOGL::zoomDown()
{
    scale *= 1.1f;
}

void FractalWindowOGL::moveDown()
{
    center = QPointF(center.x(), center.y() - scale / 2);
}

void FractalWindowOGL::moveUp()
{
    center = QPointF(center.x(), center.y() + scale / 2);
}

void FractalWindowOGL::moveRight()
{
    center = QPointF(center.x() + scale / 2, center.y());
}

void FractalWindowOGL::moveLeft()
{
    center = QPointF(center.x() - scale / 2, center.y());
}
