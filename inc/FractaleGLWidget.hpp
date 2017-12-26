#ifndef FRACTALEGLWIDGET_H
#define FRACTALEGLWIDGET_H

#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QGLWidget>

class FractaleGLWidget : public QGLWidget
{
    Q_OBJECT

    public:
        explicit FractaleGLWidget(int framesPerSecond = 0, QWidget *parent = 0,
                const char *name = 0);
        virtual void initializeGL() = 0;
        virtual void resizeGL(int width, int height) = 0;
        virtual void paintGL() = 0;
        virtual void keyPressEvent(QKeyEvent *keyEvent);
        void toggleFullWindow();

    public slots:
        virtual void timeOutSlot();

    private:
        QTimer *t_Timer;
};

#endif /* ifndef FRACTALEGLWIDGET_H */
