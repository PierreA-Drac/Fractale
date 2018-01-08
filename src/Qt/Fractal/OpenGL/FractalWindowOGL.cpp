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

FractalWindowOGL::FractalWindowOGL(type fracType, float zMax, float cReal,
        float cImg, bool coul, QWidget *parent)
    : FractalWindow(fracType, FractalWindow::OPENGL, zMax, cReal, cImg, coul,
            parent, 60), center(0.f, 0.f), scale(1.5)
{
}

void FractalWindowOGL::initializeGL()
{
    /* Initialisation d'OpenGL. */
    qglClearColor(QColor(Qt::black));
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    /* Initialisation des shaders. */
    std::string fragShader =
        QCoreApplication::applicationDirPath().toStdString();
    std::string vertShader =
        QCoreApplication::applicationDirPath().toStdString().append(
                "/Shaders/vertexShader.vsh");
    if (fracType == MANDELBROT)
        fragShader.append("/Shaders/fragmentShaderMandelbrot.fsh");
    else if (fracType == JULIA)
        fragShader.append("/Shaders/fragmentShaderJulia.fsh");

    shaderProgram = new QGLShaderProgram(context(), this);
    if (!shaderProgram->addShaderFromSourceFile(QGLShader::Vertex,
                vertShader.data())
            || !shaderProgram->addShaderFromSourceFile(QGLShader::Fragment,
                fragShader.data())
            || !shaderProgram->link()) {
        throw std::runtime_error("Shader initialization failed");
    }
}

void FractalWindowOGL::resizeGL(int width, int height)
{
    /* Évite la division par 0. */
    if (height == 0)
        height = 1;
    /* Il faut, dans ce cas, multiplier la matrice de projection par la matrice
     * identité pour ne pas la modifier (la multiplier avec l'ancienne matrice
     * de projection). */
    pMatrix.setToIdentity();
    /* Créer la matrice de projection avec le FOV, le ratio, et les distances
     * minimale et maximale de rendu. FOV très petit pour permettre un gros
     * zoom. */
    pMatrix.perspective(80, (float)width / (float)height, 0.001, 1000);
    /* Fait correspondre la matrice projection avec la zone du widget dans le
     * contexte OpenGL. Évite les distorsions et le placage des éléments aux
     * mauvais endroits. */
    glViewport(0, 0, width, height);
}

void FractalWindowOGL::paintGL()
{
    /* Préparation de l'écran et du pipeline 3D. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderProgram->bind();

    /* Incrémentation des itérations maximum pour l'effet de dessin sur l'écran
     * à l'ouverture d'une fenêtre de fractale OGL. */
    if (n <= nMax)
        n++;

    /* Transfert des variables globales (uniformes) aux shaders. */
    shaderProgram->setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);
    shaderProgram->setUniformValue("n_max", n);
    shaderProgram->setUniformValue("c", c);
    shaderProgram->setUniformValue("z_max", zMax * zMax);
    shaderProgram->setUniformValue("z_0", z0);
    shaderProgram->setUniformValue("b_color", coul);
    shaderProgram->setUniformValue("scale", scale);
    shaderProgram->setUniformValue("center", center);

    /* Vertices d'un rectangle qui rempli l'écran (même avec plusieurs
     * ratio différents). */
    quadVertices
        << QVector3D(-6, -2, -1)
        << QVector3D( 6, -2, -1)
        << QVector3D( 6,  2, -1)
        << QVector3D(-6,  2, -1);

    /* Transfert de l'entrée du Vertex Shader. */
    shaderProgram->setAttributeArray("vertex", quadVertices.constData());
    shaderProgram->enableAttributeArray("vertex");

    /* Dessin du carré sur l'écran. */
    glDrawArrays(GL_QUADS, 0, quadVertices.size());

    /* Libération de l'entrée du shader et désactivation dans le pipeline. */
    shaderProgram->disableAttributeArray("vertex");
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
