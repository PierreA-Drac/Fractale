/**
 * @file FractalWindowOGL.cpp
 * @brief Fenêtre d'une fractale rendu avec OpenGL.
 *
 * Implémentation de la classe de la fenêtre d'une fractale rendu avec OpenGL.
 */

#include "FractalWindowOGL.hpp"

#include <QtCore/QDebug>
#include "QtCore/QString"

#include "MainWindow.hpp"

FractalWindowOGL::FractalWindowOGL(type fracType, bool coul, QWidget *parent) 
    : FractalWindow(fracType, FractalWindow::OPENGL, parent, 60)
    , iterations(512) , centre(0.f, 0.f) , scale(1.f) , coul(coul)
{  
}

void FractalWindowOGL::JuliaFractal()
{
    QString code = "uniform int iterations;"
        "uniform highp vec2 c;\n"
        "uniform highp vec2 centre;\n"
        "uniform highp float scale;\n"

        "varying highp vec2 texture_out;\n"

        "void main()\n"
        "{\n"
            "vec2 z;\n"
            "z.x = scale * ( 3.0 * texture_out.x - 2.0 ) + centre.x;\n"
            "z.y = scale * ( 2.0 * texture_out.y - 1.0 ) + centre.y;\n"

            " int i = 0;\n"
            " for(; i < iterations; ++i)\n"
            " {\n"
                "float x = z.x*z.x - z.y*z.y + c.x;\n"
                "float y = z.x*z.y + z.y*z.x + c.y;\n"

                "if( x*x + y*y > 4.0 )\n"
                "  break;\n"

                "z.x = x;\n"
                "z.y = y;\n"
            "}\n"

            "vec4 color = vec4(0.0);\n"

            "if(i < iterations - 1)\n";
    // En noir et blanc
    if(coul == false)
        code += "color = vec4(1.0);\n";
    // En couleur
    else
        code += " {\n"
                "color.x = sin(float(i) / 100.0);\n"
                "color.y = sin(float(i) / 70.0);\n"
                "color.z = cos(float(i) / 20.0 + 3.141 / 4.0);\n"
            "}\n";

    code += "gl_FragColor = color;\n"
        "}";
    shaderProgram = new QGLShaderProgram(context(), this);
    shaderProgram->addShader(vertexShader);
    //~ shaderProgram->addShaderFromSourceFile(QGLShader::Fragment,
    //~ ":/Julia.glsl");
    shaderProgram->addShaderFromSourceCode(QGLShader::Fragment, code);
    shaderProgram->link();
    shaderProgram->bind();
}

void FractalWindowOGL::MandelbrotFractal()
{
    QString code = "uniform int iterations;"
        "uniform highp vec2 centre;\n"
        "uniform highp float scale;\n"

        "varying highp vec2 texture_out;\n"

        "void main()\n"
        "{\n"
            "vec2 z;\n"
            "vec2 c;\n"
            "c.x = scale * ( 3.0 * texture_out.x - 2.0 ) + centre.x;\n"
            "c.y = scale * ( 2.0 * texture_out.y - 1.0 ) + centre.y;\n"

            "z = c;\n"

            " int i = 0;\n"
            " for(; i < iterations; ++i)\n"
            " {\n"
                "float x = z.x*z.x - z.y*z.y + c.x;\n"
                "float y = z.x*z.y + z.y*z.x + c.y;\n"

                "if( x*x + y*y > 4.0 )\n"
                "  break;\n"

                "z.x = x;\n"
                "z.y = y;\n"
            "}\n"

            "vec4 color = vec4(0.0);\n"

            "if(i < iterations - 1)\n";
    // En noir et blanc
    if(coul == false)
        code += "color = vec4(1.0);\n";
    // En couleur
    else
        code += " {\n"
                "color.x = sin(float(i) / 100.0);\n"
                "color.y = sin(float(i) / 70.0);\n"
                "color.z = cos(float(i) / 20.0 + 3.141 / 4.0);\n"
            "}\n";

    code += "gl_FragColor = color;\n"
        "}";
    shaderProgram = new QGLShaderProgram(context(), this);
    shaderProgram->addShader(vertexShader);
    //shaderProgram->addShaderFromSourceFile(QGLShader::Fragment,
    //              "/home/user/Bureau/Info.L3/Fractale/Mandelbrot.glsl");
    shaderProgram->addShaderFromSourceCode(QGLShader::Fragment, code);
    shaderProgram->link();
    shaderProgram->bind();
}

void FractalWindowOGL::initializeGL()
{
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    vertexShader = new QGLShader(QGLShader::Vertex, this);
    vertexShader->compileSourceCode(
            "attribute highp vec4 vertex;\n"
            "attribute highp vec2 texture_in;\n"
            "varying   highp vec2 texture_out;\n"
            "void main()\n"
            "{\n"
            "  gl_Position = vertex;\n"
            "  texture_out = texture_in;\n"
            "}\n");
    if(fracType == MANDELBROT)
        this->MandelbrotFractal();
    else
        this->JuliaFractal();
}

void FractalWindowOGL::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void FractalWindowOGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram->setUniformValue("scale", scale);
    shaderProgram->setUniformValue("centre", centre);
    shaderProgram->setUniformValue("iterations", iterations);
    //~ shaderProgram->setUniformValue("c", QPointF(1.0, 1.0));
    shaderProgram->setUniformValue("c", QPointF(-0.577,0.478)); //Pour Julia
    //shaderProgram->setUniformValue("c", QPointF(-0.0519,0.688)); //Pour Julia

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

    int vertexLocation  = shaderProgram->attributeLocation("vertex");
    int textureLocation = shaderProgram->attributeLocation("texture_in");

    shaderProgram->enableAttributeArray(vertexLocation);
    shaderProgram->setAttributeArray(vertexLocation, quadVertices, 2);
    shaderProgram->enableAttributeArray(textureLocation);
    shaderProgram->setAttributeArray(textureLocation, textureCoordinates, 2);

    glDrawArrays(GL_QUADS, 0, 4);
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

void FractalWindowOGL::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key()) {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_F2:
            toggleFullWindow();
            break;
        case Qt::Key_Plus:
            zoomUp();
            break;
        case Qt::Key_Minus:
            zoomDown();
            break;
        case Qt::Key_Up:
            moveUp();
            break;
        case Qt::Key_Down:
            moveDown();
            break;
        case Qt::Key_Right:
            moveRight();
            break;
        case Qt::Key_Left:
            moveLeft();
            break;
        default:
            {
                if (MainWindow *ptr = (MainWindow *)parentWidget())
                    ptr->keyPressEvent(keyEvent);
                break;
            }
    }
}
