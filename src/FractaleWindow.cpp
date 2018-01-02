#include "MainWindow.hpp"
#include <QtCore/QDebug>
#include "FractaleWindow.hpp"
#include "QtCore/QString"

FractaleWindow::FractaleWindow(bool fracType, bool coul, QWidget *parent) 
    : FractaleGLWidget(60, parent, "Fractale de ? avec ?")
    , _iterations(512)
  , _centre(0.f, 0.f)
  , _scale(1.f)
  , _fracType(fracType)
  , _coul(coul)
{  
}

void FractaleWindow::JuliaFractal()
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

			"if(i < iterations - 1)\n";
    //en noir et blanc
    if(_coul == BLACK_WHITE)
        code += "color = vec4(1.0);\n";
	//en couleur
    else
		code += " {\n"
				"color.x = sin(float(i) / 100.0);\n"
				"color.y = sin(float(i) / 70.0);\n"
				"color.z = cos(float(i) / 20.0 + 3.141 / 4.0);\n"
			  "}\n";

    code += "gl_FragColor = color;\n"
			"}";
    _shaderProgram = new QGLShaderProgram(context(), this);
  _shaderProgram->removeAllShaders();
  _shaderProgram->addShader(_vertexShader);
  //~ _shaderProgram->addShaderFromSourceFile(QGLShader::Fragment,
                                             //~ ":/Julia.glsl");
  _shaderProgram->addShaderFromSourceCode(QGLShader::Fragment, code);
  _shaderProgram->link();
  _shaderProgram->bind();
}

void FractaleWindow::MandelbrotFractal()
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

			  "if(i < iterations - 1)\n";
	//en noir et blanc
    if(_coul == BLACK_WHITE)
        code += "color = vec4(1.0);\n";
	//en couleur
    else
		code += " {\n"
				"color.x = sin(float(i) / 100.0);\n"
				"color.y = sin(float(i) / 70.0);\n"
				"color.z = cos(float(i) / 20.0 + 3.141 / 4.0);\n"
			  "}\n";

		code += "gl_FragColor = color;\n"
			"}";

    _shaderProgram = new QGLShaderProgram(context(), this);
  _shaderProgram->removeAllShaders();
  _shaderProgram->addShader(_vertexShader);
  //_shaderProgram->addShaderFromSourceFile(QGLShader::Fragment,
    //              "/home/user/Bureau/Info.L3/Fractale/Mandelbrot.glsl");
  _shaderProgram->addShaderFromSourceCode(QGLShader::Fragment, code);

  _shaderProgram->link();
  _shaderProgram->bind();
}
void FractaleWindow::initializeGL()
{
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
  
  if(_fracType == MANDELBROT)
    this->MandelbrotFractal();
  else
    this->JuliaFractal();
}

void FractaleWindow::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void FractaleWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _shaderProgram->setUniformValue("scale", _scale);
  _shaderProgram->setUniformValue("centre", _centre);
  _shaderProgram->setUniformValue("iterations", _iterations);
  //~ _shaderProgram->setUniformValue("c", QPointF(1.0, 1.0));
  _shaderProgram->setUniformValue("c", QPointF(-0.577,0.478)); //Pour Julia
  //_shaderProgram->setUniformValue("c", QPointF(-0.0519,0.688)); //Pour Julia

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

  int vertexLocation  = _shaderProgram->attributeLocation("vertex");
  int textureLocation = _shaderProgram->attributeLocation("texture_in");

  _shaderProgram->enableAttributeArray(vertexLocation);
  _shaderProgram->setAttributeArray(vertexLocation, quadVertices, 2);
  _shaderProgram->enableAttributeArray(textureLocation);
  _shaderProgram->setAttributeArray(textureLocation, textureCoordinates, 2);

  glDrawArrays(GL_QUADS, 0, 4);
}


void FractaleWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    bool update = false;
    switch(keyEvent->key()) {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_F2:
            toggleFullWindow();
            break;
        case Qt::Key_Plus:
            _scale *= 0.9f;
            update  = true;
            break;
        case Qt::Key_Minus:
            _scale *= 1.1f;
            update = true;    
            break;
        case Qt::Key_Up:
            _centre = QPointF(_centre.x(), _centre.y() + _scale / 2);
            update = true;
            break;
        case Qt::Key_Down:
            _centre = QPointF(_centre.x(), _centre.y() -_scale / 2);
            update = true;
            break;
        case Qt::Key_Right:
            _centre = QPointF(_centre.x() + _scale / 2, _centre.y());
            update = true;
            break;
        case Qt::Key_Left:
            _centre = QPointF(_centre.x() - _scale / 2, _centre.y());
            update = true;
            break;
        default:
            {
                if (MainWindow *ptr = (MainWindow *)parentWidget())
                    ptr->keyPressEvent(keyEvent);
                break;
            }
    }
    if(update)
        this->updateGL();
}

