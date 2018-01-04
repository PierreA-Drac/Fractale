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
    , centre(0.f, 0.f) , scale(1.f)
{
}

void FractalWindowOGL::initializeGL()
{
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

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

    shaderProgram->bind();
    shaderProgram->setUniformValue("scale", scale);
    shaderProgram->setUniformValue("centre", centre);
    shaderProgram->setUniformValue("iterations", nMax);
    shaderProgram->setUniformValue("b_color", coul);
    // shaderProgram->setUniformValue("c", QPointF(1.0, 1.0));
    shaderProgram->setUniformValue("c", QPointF(-0.577,0.478)); // Pour Julia
    // shaderProgram->setUniformValue("c", QPointF(-0.0519,0.688)); // Pour Julia

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
    centre = QPointF(centre.x(), centre.y() -scale / 2);
}

void FractalWindowOGL::moveUp()
{
    centre = QPointF(centre.x(), centre.y() + scale / 2);
}

void FractalWindowOGL::moveRight()
{
    centre = QPointF(centre.x() + scale / 2, centre.y());
}

void FractalWindowOGL::moveLeft()
{
    centre = QPointF(centre.x() - scale / 2, centre.y());
}
