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
        FractalWindow(QWidget *parent = 0, const char *name = 0,
                int framesPerSecond = 0);
        void keyPressEvent(QKeyEvent *keyEvent);
        void toggleFullWindow();

    public slots:
        virtual void updateWin() = 0;

    private:
        // A tester destrcteur pour détruire QTimer
        QTimer *t_Timer;
};

#endif /* ifndef FRACTALWINDOW_H */
