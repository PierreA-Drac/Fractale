#include "testglwidget.hpp"


#include <QtCore/QDebug>
#include <QtGui/QKeyEvent>
//#include <QtGui/QMouseEvent>

RenderWidget::RenderWidget(QWidget* parent)
  : QGLWidget(parent)
  , _iterations(512)
  , _centre(0.f, 0.f)
  , _scale(1.f)
{
  this->setFocusPolicy(Qt::StrongFocus);
}

RenderWidget::~RenderWidget()
{
}

void RenderWidget::loadJuliaFractal()
{
  _shaderProgram.removeAllShaders();
  _shaderProgram.addShader(_vertexShader);
  _shaderProgram.addShaderFromSourceFile(QGLShader::Fragment,
                                             ":/Julia.glsl");

  _shaderProgram.link();
  _shaderProgram.bind();
}

void RenderWidget::loadMandelbrotFractal()
{
  char* code = "uniform int iterations;"
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
			"  for(; i < iterations; ++i)\n"
			"  {\n"
				"float x = z.x*z.x - z.y*z.y + c.x;\n"
				"float y = z.x*z.y + z.y*z.x + c.y;\n"

				"if( x*x + y*y > 4.0 )\n"
				"  break;\n"

				"z.x = x;\n"
				"z.y = y;\n"
			  "}\n"

			  "vec4 color = vec4(0.0);\n"

			  "if(i < iterations - 1)\n"
	//en noir et blanc
			  "color = vec4(1.0);\n"
	//en couleur
			 /*" {\n"
				"color.x = sin(float(i) / 100.0);\n"
				"color.y = sin(float(i) / 100.0);\n"
				"color.z = cos(float(i) / 100.0 + 3.141 / 4.0);\n"
			  "}\n"*/

			  "gl_FragColor = color;\n"
			"}";
  _shaderProgram.removeAllShaders();
  _shaderProgram.addShader(_vertexShader);
  //_shaderProgram.addShaderFromSourceFile(QGLShader::Fragment,
    //              "/home/user/Bureau/Info.L3/Fractale/Mandelbrot.glsl");
  _shaderProgram.addShaderFromSourceCode(QGLShader::Fragment, code);

  _shaderProgram.link();
  _shaderProgram.bind();
}

void RenderWidget::initializeGL()
{
  //this->initializeOpenGLFunctions();
  this->qglClearColor(Qt::black);

  glEnable(GL_DEPTH_TEST);

  _vertexShader = new QGLShader(QGLShader::Vertex, this);

  _vertexShader->compileSourceCode(
     "attribute highp vec4 vertex;\n"
     "attribute highp vec2 texture_in;\n"
     "varying   highp vec2 texture_out;\n"
     "void main()\n"
     "{\n"
     "  gl_Position = vertex;\n"
     "  texture_out = texture_in;\n"
     "}\n");

  this->loadMandelbrotFractal();
}

void RenderWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void RenderWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _shaderProgram.setUniformValue("scale", _scale);
  _shaderProgram.setUniformValue("centre", _centre);
  _shaderProgram.setUniformValue("iterations", _iterations);
  _shaderProgram.setUniformValue("c", QPointF(-1.0,0.1));

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

  int vertexLocation  = _shaderProgram.attributeLocation("vertex");
  int textureLocation = _shaderProgram.attributeLocation("texture_in");

  _shaderProgram.enableAttributeArray(vertexLocation);
  _shaderProgram.setAttributeArray(vertexLocation, quadVertices, 2);
  _shaderProgram.enableAttributeArray(textureLocation);
  _shaderProgram.setAttributeArray(textureLocation, textureCoordinates, 2);

  glDrawArrays(GL_QUADS, 0, 4);
}

void RenderWidget::mousePressEvent(QMouseEvent* event)
{
  /*double xrange[] = { ( -2.0 * _scale + _centre.x() ), ( 1.0 * _scale + _centre.x() ) };
  double yrange[] = { ( -1.0 * _scale + _centre.y() ), ( 1.0 * _scale +  _centre.y() ) };

  QPointF windowPosition   = event->windowPos();
  QPointF absolutePosition = QPointF(  ( xrange[1] - xrange[0] ) / this->width() * windowPosition.x()  + xrange[0],
                                      -( yrange[1] - yrange[0] ) / static_cast<float>(this->height()) * windowPosition.y() + yrange[1] );

  _centre = absolutePosition;

  this->update();*/
}

void RenderWidget::keyPressEvent(QKeyEvent* event)
{
  bool update = false;

  if(event->type() == QEvent::KeyPress)
  {
    if(event->key() == Qt::Key_Plus)
    {
      _scale *= 0.9f;
      update  = true;
    }
    else if(event->key() == Qt::Key_Minus)
    {
      _scale *= 1.1f;
      update = true;
    }
  }

  if(update)
    this->update();
}
