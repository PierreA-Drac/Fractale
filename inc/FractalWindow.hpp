#ifndef FRACTALWINDOW_H
#define FRACTALWINDOW_H

#include <QtCore/QTimer>
#include <QtGui/QWidget>
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QGLWidget>

class FractalWindow : public QGLWidget
{
    Q_OBJECT

    public:
        enum type   {MANDELBROT, JULIA, FRAC_TYPE_NBR_ELMT};
        enum render {OPENGL, CAIRO, RENDER_NBR_ELMT};
        FractalWindow(type t_fracType, render t_fracRender, QWidget *parent = 0,
                int framesPerSecond = 0);
        ~FractalWindow();
        void keyPressEvent(QKeyEvent *keyEvent);
        void toggleFullWindow();
        const char* getRenderStr() const;

    public slots:
        virtual void updateWin() = 0;

    protected:
        type   fracType;
        render fracRender;
        const char* typeStr[FRAC_TYPE_NBR_ELMT] = {
            "Mandelbrot",
            "Julia et Fatou"
        };
        const char* renderStr[RENDER_NBR_ELMT] = {
            "OpenGL",
            "Cairo"
        };

    private:
        QTimer *timer;
};

#endif /* ifndef FRACTALWINDOW_H */
