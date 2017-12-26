#include "testglwidget.hpp"

GLWidget::GLWidget( const QGLFormat& format, QWidget* parent )
 : QGLWidget( format, parent ),
 m_vertexBuffer( QGLBuffer::VertexBuffer )
{
}

void GLWidget::initializeGL()
{
 //~ QGLFormat glFormat = QGLWidget::format();
 //~ if ( !glFormat.sampleBuffers() )
 //~ qWarning() << "Could not enable sample buffers";

// Set the clear color to black
 glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

// Prepare a complete shader program…
 if ( !prepareShaderProgram( ":/vertex.vsh", ":/fragment.fsh" ) )
 return;

// We need us some vertex data. Start simple with a triangle ;-)
 float points[] = {  60.0f,  10.0f,  0.0f,
     110.0f, 110.0f, 0.0f,
     10.0f,  110.0f, 0.0f };
 m_vertexBuffer.create();
 m_vertexBuffer.setUsagePattern( QGLBuffer::StaticDraw );
 if ( !m_vertexBuffer.bind() )
 {
 qWarning() << "Could not bind vertex buffer to the context";
 return;
 }
 m_vertexBuffer.allocate( points, 3 * 4 * sizeof( float ) );

 // Bind the shader program so that we can associate variables from
 // our application to the shaders
 if ( !m_shader.bind() )
 {
 qWarning() << "Could not bind shader program to context";
 return;
 }

 // Enable the "vertex" attribute to bind it to our currently bound
 // vertex buffer.
 m_shader.setAttributeBuffer( "vertex", GL_FLOAT, 0, 4 );
 m_shader.enableAttributeArray( "vertex" );
}

bool GLWidget::prepareShaderProgram( const QString& vertexShaderPath,
 const QString& fragmentShaderPath )
{
 // First we load and compile the vertex shader…
 //bool result = m_shader.addShaderFromSourceFile( QGLShader::Vertex, vertexShaderPath );
 bool result = m_shader.addShaderFromSourceCode( QGLShader::Vertex, 
		"#version 330\n"
		"in vec4 vertex;\n"
		"in mat4 matrix;\n"
		"void main( void )\n"
		"{\n"
		"gl_Position = vertex*matrix;\n"
		"}");
 if ( !result )
 qWarning() << m_shader.log();

// …now the fragment shader…
 //result = m_shader.addShaderFromSourceFile( QGLShader::Fragment, fragmentShaderPath );
 result = m_shader.addShaderFromSourceCode( QGLShader::Fragment, 
		"#version 330\n"
		"layout(location = 0, index = 0) out vec4 fragColor;\n"
		"void main( void )\n"
		"{\n"
		"fragColor = vec4( 1.0, 0.0, 0.0, 1.0 );\n"
		"}");
 if ( !result )
 qWarning() << m_shader.log();

// …and finally we link them to resolve any references.
 result = m_shader.link();
 if ( !result )
 qWarning() << "Could not link shader program:" << m_shader.log();

return result;
}

void GLWidget::resizeGL( int w, int h )
{
 // Set the viewport to window dimensions
 glViewport( 0, 0, w, qMax( h, 1 ) );
}

void GLWidget::paintGL()
{
 // Clear the buffer with the current clearing color
 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

// Draw stuff
 glDrawArrays( GL_TRIANGLES, 0, 3 );
}

void GLWidget::keyPressEvent( QKeyEvent* e )
{
 switch ( e->key() )
 {
 case Qt::Key_Escape:
 QCoreApplication::instance()->quit();
 break;

 default:
 QGLWidget::keyPressEvent( e );
 }
}
